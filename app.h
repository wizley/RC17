#ifndef _APP_H_
#define _APP_H_

/**
 * @brief An application entry, used by the menu application.
 */
typedef struct {
    ///> Application name
    const char* name;

    /**
     * @brief Main application routine.
     * @params Optional parameters, dependendent on application.
     */
    void (*main)(void* params);
} application;

int app_init(void);

#endif
