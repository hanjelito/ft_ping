#include <stdio.h>
#include <string.h>

typedef struct {
    const char *target;
} PingConfig;

void init_config(PingConfig *config) {
    config->target = NULL;
}

void flag_h(const char *program_name) {
    printf("solicitaste ayudas\n");
}

void flag_t(const char *program_name) {
    printf("solicitaste flag t\n");
}

int parse_arguments(int argc, char *argv[], PingConfig *config) {
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            char flag = argv[i][1];
            if (flag == 'h' && strlen(argv[i]) == 2) {
                flag_h(argv[0]);
                return 2;
            } else if (flag == 't' && config->target == NULL) {
                flag_t(argv[0]);
                return 2;
            } else {
                printf("Error flag desconocido\n");
                return 0;
            }
        } else {
            if (config->target != NULL) {
                printf("Error: solo se permite un argumento\n");
                printf("    Ya tengo: '%s', intentas agregar '%s'\n", config->target, argv[i]);
                return 0;
            }
            config->target = argv[i];
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No tiene argumentos\n");
        return 1;
    }

    PingConfig config;
    init_config(&config);

    int result = parse_arguments(argc, argv, &config);

    if (result == 2) {
        return 0;
    }

    if (result == 0) {
        printf("\n Debes usar '%s -h' para ver la ayuda", argv[0]);
        return 1;
    }

    if (config.target == NULL) {
        printf("Error: debes especificar un destino\n");
        printf("'%s 8.8.8.8 -h'\n", argv[0]);
        return 1;
    }

    return 0;
}