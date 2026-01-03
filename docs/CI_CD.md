# CI/CD Pipeline Documentation

## Overview

SimpleOS uses GitHub Actions for continuous integration and continuous deployment. This document explains the automated workflows and how to use them.

## Workflows

### 1. Build Workflow (`.github/workflows/build.yml`)

**Triggers:**
- Push to `main` or `develop` branches
- Pull requests to `main` branch
- Manual workflow dispatch

**Jobs:**

#### Build Job
Compiles the operating system and creates build artifacts.

**Steps:**
1. Checkout code
2. Install dependencies (NASM, QEMU, build tools)
3. Install i686-elf cross-compiler
4. Verify toolchain installation
5. Build bootloader
6. Build kernel
7. Build complete OS image
8. Verify build artifacts
9. Check OS image size
10. Upload artifacts to GitHub

**Artifacts:**
- `os-image`: Complete bootable OS image (30-day retention)
- `build-artifacts`: All build files including object files (7-day retention)

#### Test Job
Tests the OS boot process in QEMU.

**Steps:**
1. Download built OS image
2. Install QEMU
3. Test boot in headless mode
4. Capture serial output
5. Verify boot process

#### Lint Job
Performs code quality checks.

**Checks:**
- File permissions (no executable source files)
- Trailing whitespace detection
- Required documentation files

### 2. Release Workflow (`.github/workflows/release.yml`)

**Triggers:**
- Push of version tags (format: `v*.*.*`, e.g., `v0.1.0`)
- Manual workflow dispatch

**Steps:**
1. Extract version from git tag
2. Install build dependencies
3. Build OS with release configuration
4. Create release package with:
   - Bootable OS image
   - Bootloader binary
   - Kernel binary
   - Documentation (README, LICENSE)
   - Release notes
5. Generate SHA256 checksums
6. Create compressed archives (tar.gz and zip)
7. Create GitHub release with artifacts
8. Upload release artifacts

**Release Artifacts:**
- `SimpleOS-vX.X.X.bin` - Bootable OS image
- `SimpleOS-vX.X.X.tar.gz` - Complete release archive (tar.gz)
- `SimpleOS-vX.X.X.zip` - Complete release archive (zip)
- `SHA256SUMS` - Checksums for verification

## Using the CI/CD Pipeline

### Viewing Build Status

1. Go to the [Actions tab](https://github.com/Jybhavsar12/Operating_system/actions)
2. Click on a workflow run to see details
3. View logs for each job and step

### Downloading Build Artifacts

1. Navigate to a successful workflow run
2. Scroll to the "Artifacts" section at the bottom
3. Click on the artifact name to download
4. Extract and use the OS image

### Creating a Release

To create a new release:

```bash
# 1. Update version in code if needed
# 2. Commit all changes
git add .
git commit -m "Prepare release v0.2.0"

# 3. Create and push a version tag
git tag -a v0.2.0 -m "Release version 0.2.0"
git push origin v0.2.0

# 4. GitHub Actions will automatically:
#    - Build the OS
#    - Create release artifacts
#    - Publish a GitHub release
```

### Manual Workflow Trigger

You can manually trigger workflows:

1. Go to Actions tab
2. Select the workflow (Build or Release)
3. Click "Run workflow"
4. Select branch
5. Click "Run workflow" button

## Build Environment

### Ubuntu Latest (GitHub-hosted runner)

**Installed Tools:**
- NASM (Netwide Assembler)
- QEMU (x86 system emulator)
- Build essentials (make, gcc, etc.)
- i686-elf cross-compiler (downloaded from GitHub releases)

**Compiler Versions:**
- i686-elf-gcc 7.1.0
- NASM 2.15+
- GNU Make 4.3+

## Troubleshooting

### Build Failures

**Cross-compiler not found:**
- Check if the download URL is still valid
- Verify the PATH is set correctly
- Try using a different cross-compiler source

**NASM errors:**
- Verify NASM syntax in assembly files
- Check NASM version compatibility

**Linker errors:**
- Verify all object files are being linked
- Check linker script and flags
- Ensure all symbols are defined

### Test Failures

**QEMU timeout:**
- OS may be stuck in a loop
- Check for infinite loops in kernel code
- Verify interrupt handling

**Boot failure:**
- Check bootloader code
- Verify boot signature (0x55AA)
- Ensure kernel is loaded correctly

## Best Practices

### For Contributors

1. **Test locally before pushing:**
   ```bash
   make clean
   make all
   make run
   ```

2. **Keep commits atomic:**
   - One logical change per commit
   - Clear commit messages

3. **Update documentation:**
   - Update relevant docs when changing features
   - Keep README.md current

4. **Check build status:**
   - Wait for CI to pass before merging
   - Fix any warnings or errors

### For Maintainers

1. **Review CI logs regularly**
2. **Keep dependencies updated**
3. **Monitor artifact storage usage**
4. **Test releases before publishing**

## Future Enhancements

Potential CI/CD improvements:

- [ ] Add automated testing framework
- [ ] Implement code coverage reporting
- [ ] Add static analysis tools
- [ ] Create nightly builds
- [ ] Add performance benchmarks
- [ ] Implement automated deployment to documentation site
- [ ] Add security scanning
- [ ] Create Docker-based build environment

## Resources

- [GitHub Actions Documentation](https://docs.github.com/en/actions)
- [Workflow Syntax](https://docs.github.com/en/actions/reference/workflow-syntax-for-github-actions)
- [GitHub Actions Marketplace](https://github.com/marketplace?type=actions)

