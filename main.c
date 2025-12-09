#include "app.h"

int main(int argc, char *argv[]){
    bool exit_status = EXIT_FAILURE;

    App *app = NULL;

    if (app_new(&app)) {
        app_run(app);        
        exit_status = EXIT_SUCCESS;
    }

    app_free(&app);

    return exit_status;
}