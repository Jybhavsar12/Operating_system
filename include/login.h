/**
 * login.h - Login screen interface
 */

#ifndef LOGIN_H
#define LOGIN_H

#include "types.h"

/**
 * login_init - Initialize login screen
 */
void login_init(void);

/**
 * login_draw - Draw the login screen
 */
void login_draw(void);

/**
 * login_handle_key - Handle keyboard input
 * @c: Character pressed
 */
void login_handle_key(char c);

/**
 * login_attempt - Attempt login with current credentials
 */
void login_attempt(void);

/**
 * login_is_successful - Check if login succeeded
 *
 * Return: true if logged in
 */
bool login_is_successful(void);

/**
 * login_is_active - Check if login screen is active
 *
 * Return: true if showing
 */
bool login_is_active(void);

#endif // LOGIN_H

