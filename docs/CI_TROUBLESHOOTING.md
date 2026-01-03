# CI/CD Troubleshooting Guide

## Common Issues and Solutions

### Issue 1: Exit Code 127 - Command Not Found

**Symptom:**
```
Process completed with exit code 127
```

**Cause:**
The cross-compiler (i686-elf-gcc or i686-elf-ld) is not found in PATH.

**Solution:**
1. Check if the cross-compiler download succeeded
2. Verify the PATH is set correctly
3. Ensure the toolchain is extracted to the right location

**Fixed in commit:** `716182d` - Changed to reliable newos.org toolchain

---

### Issue 2: Cross-Compiler Download Fails

**Symptom:**
```
wget: unable to resolve host address
404 Not Found
```

**Cause:**
The download URL for the cross-compiler is unavailable or has changed.

**Solutions:**

**Option A: Use newos.org toolchain (current)**
```yaml
wget https://newos.org/toolchains/i686-elf-4.9.1-Linux-x86_64.tar.xz
sudo tar -xf i686-elf-4.9.1-Linux-x86_64.tar.xz -C /usr/local
echo "/usr/local/cross/bin" >> $GITHUB_PATH
```

**Option B: Build from source (slower but reliable)**
```yaml
# Install build dependencies
sudo apt-get install -y libgmp-dev libmpfr-dev libmpc-dev texinfo

# Download and build binutils and gcc
# See full script in docs/BUILDING.md
```

**Option C: Use Docker container**
```yaml
docker pull randomdude/gcc-cross-x86_64-elf
# Create wrapper scripts for i686-elf-gcc and i686-elf-ld
```

---

### Issue 3: NASM Not Found

**Symptom:**
```
nasm: command not found
```

**Solution:**
```yaml
- name: Install dependencies
  run: |
    sudo apt-get update
    sudo apt-get install -y nasm
```

---

### Issue 4: QEMU Timeout During Testing

**Symptom:**
```
timeout: the monitored command dumped core
```

**Cause:**
The OS is stuck in an infinite loop or crashed during boot.

**Solutions:**
1. Test locally first: `make run`
2. Check kernel code for infinite loops
3. Verify interrupt handling is correct
4. Add debug output to identify where it hangs

**Debug with serial output:**
```bash
qemu-system-i386 -drive format=raw,file=build/os-image.bin -serial stdio
```

---

### Issue 5: Linker Errors

**Symptom:**
```
i686-elf-ld: cannot find entry symbol _start
undefined reference to `function_name`
```

**Solutions:**

**Missing _start symbol:**
- Ensure `kernel_entry.asm` defines `global _start`
- Check that kernel_entry.o is first in link order

**Undefined references:**
- Verify all .c files are compiled
- Check function declarations match definitions
- Ensure all object files are linked

---

### Issue 6: Build Artifacts Not Uploaded

**Symptom:**
```
Warning: No files were found with the provided path
```

**Cause:**
Build failed before artifacts were created, or path is incorrect.

**Solution:**
1. Check that build completed successfully
2. Verify artifact paths in workflow:
```yaml
- uses: actions/upload-artifact@v4
  with:
    name: os-image
    path: build/os-image.bin  # Must exist
```

---

### Issue 7: Cache Not Working

**Symptom:**
Cross-compiler downloads every time, slowing builds.

**Solution:**
Add caching to workflow:
```yaml
- name: Cache cross-compiler
  uses: actions/cache@v4
  with:
    path: /usr/local/cross
    key: i686-elf-gcc-4.9.1
```

---

### Issue 8: Workflow Not Triggering

**Symptom:**
Push to GitHub but workflow doesn't run.

**Causes & Solutions:**

**Wrong branch:**
- Check workflow triggers in `.github/workflows/build.yml`
- Ensure you're pushing to `main` or `develop`

**Workflow disabled:**
- Go to Actions tab → Select workflow → Enable if disabled

**Syntax error in workflow:**
- Check YAML syntax
- Look for indentation errors
- Validate with: https://www.yamllint.com/

---

## Debugging Workflows

### View Detailed Logs

1. Go to Actions tab
2. Click on failed workflow run
3. Click on failed job
4. Expand each step to see output
5. Look for error messages in red

### Enable Debug Logging

Add to workflow:
```yaml
env:
  ACTIONS_STEP_DEBUG: true
  ACTIONS_RUNNER_DEBUG: true
```

### Test Locally

Before pushing, test the build locally:
```bash
# Clean build
make clean

# Build everything
make all

# Test in QEMU
make run
```

---

## Quick Fixes

### Force Re-run Workflow
1. Go to Actions tab
2. Click on workflow run
3. Click "Re-run all jobs"

### Clear Cache
```bash
# In workflow, add:
- name: Clear cache
  run: |
    rm -rf /usr/local/cross
```

### Skip CI
Add to commit message:
```bash
git commit -m "docs: Update README [skip ci]"
```

---

## Getting Help

If issues persist:

1. **Check workflow logs** - Most errors are explained there
2. **Search GitHub Issues** - Others may have had same problem
3. **Test locally** - Reproduce the issue on your machine
4. **Simplify** - Comment out steps to isolate the problem
5. **Ask for help** - Open an issue with:
   - Workflow run URL
   - Error message
   - What you've tried

---

## Useful Commands

### Check if URL is accessible
```bash
wget --spider https://newos.org/toolchains/i686-elf-4.9.1-Linux-x86_64.tar.xz
```

### Verify cross-compiler
```bash
i686-elf-gcc --version
i686-elf-ld --version
```

### Test build locally
```bash
docker run --rm -v "$PWD":/work -w /work ubuntu:latest bash -c "
  apt-get update && 
  apt-get install -y nasm wget && 
  cd /tmp &&
  wget https://newos.org/toolchains/i686-elf-4.9.1-Linux-x86_64.tar.xz &&
  tar -xf i686-elf-4.9.1-Linux-x86_64.tar.xz -C /usr/local &&
  export PATH=/usr/local/cross/bin:\$PATH &&
  cd /work &&
  make clean &&
  make all
"
```

---

## Prevention

### Before Committing

- [ ] Test build locally: `make clean && make`
- [ ] Test in QEMU: `make run`
- [ ] Check for syntax errors
- [ ] Verify all files are committed
- [ ] Review diff: `git diff`

### Best Practices

1. **Small commits** - Easier to debug if something breaks
2. **Test locally first** - Don't rely on CI to catch errors
3. **Monitor Actions** - Check build status after pushing
4. **Keep workflows simple** - Complex workflows are harder to debug
5. **Use caching** - Speed up builds and reduce failures

---

## Resources

- [GitHub Actions Documentation](https://docs.github.com/en/actions)
- [Workflow Syntax](https://docs.github.com/en/actions/reference/workflow-syntax-for-github-actions)
- [OSDev Wiki - GCC Cross-Compiler](https://wiki.osdev.org/GCC_Cross-Compiler)

