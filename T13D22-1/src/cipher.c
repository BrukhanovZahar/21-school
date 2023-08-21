#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef LOG
#include "logger.h"
#endif

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void print_file_contents(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("n/a");
    } else {
        char c;
        int is_empty = 1;
        while ((c = fgetc(file)) != EOF) {
            putchar(c);
            is_empty = 0;
        }
        fclose(file);
        if (is_empty) {
            printf("n/a");
        }
    }
}

void append_to_file(const char *filename, const char *text) {
    FILE *file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "%s", text);
        fclose(file);
    }
}

void caesar_cipher(char *str, int shift) {
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = 'A' + (str[i] - 'A' + shift + 26) % 26;
        } else if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = 'a' + (str[i] - 'a' + shift + 26) % 26;
        }
    }
}

void process_CFiles_in_directory(const char *dirPath, int shift) {
    DIR *dir = opendir(dirPath);
    struct dirent *entry;
    if (dir == NULL) {
        printf("n/a\n");
    } else {
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_REG && strstr(entry->d_name, ".c") != NULL) {
                char filePath[256];
                //                sprintf(filePath, "%s/%s", dirPath, entry->d_name);
                filePath[0] = '\0';  // Ensure the buffer is initially empty
                strcat(filePath, dirPath);
                strcat(filePath, "/");
                strcat(filePath, entry->d_name);
                FILE *file = fopen(filePath, "r");
                if (file != NULL) {
                    char line[1000];
                    FILE *tempFile = fopen("tempfile", "w");
                    while (fgets(line, sizeof(line), file)) {
                        caesar_cipher(line, shift);
                        fprintf(tempFile, "%s", line);
                    }
                    fclose(file);
                    fclose(tempFile);
                    remove(filePath);
                    rename("tempfile", filePath);
                }
            } else if (entry->d_type == DT_REG && strstr(entry->d_name, ".h") != NULL) {
                char filePath[256];
                //                sprintf(filePath, "%s/%s", dirPath, entry->d_name);
                filePath[0] = '\0';  // Ensure the buffer is initially empty
                strcat(filePath, dirPath);
                strcat(filePath, "/");
                strcat(filePath, entry->d_name);
                FILE *file = fopen(filePath, "w");
                if (file != NULL) {
                    fclose(file);
                }
            }
        }
        closedir(dir);
    }
}

void xor_encrypt(char *str, const char *key) {
    size_t keyLength = strlen(key);
    for (size_t i = 0; i < strlen(str); ++i) {
        str[i] ^= key[i % keyLength];
    }
}

void process_CFiles_in_directory_DES(const char *directoryPath, const char *key) {
    DIR *dir = opendir(directoryPath);
    if (dir == NULL) {
        printf("n/a\n");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            const char *filename = entry->d_name;
            if (strstr(filename, ".c") != NULL) {
                char filePath[200];
                filePath[0] = '\0';  // Ensure the buffer is initially empty
                strcat(filePath, directoryPath);
                strcat(filePath, "/");
                strcat(filePath, filename);
                //                snprintf(filePath, sizeof(filePath), "%s/%s",
                //                directoryPath, filename);

                FILE *file = fopen(filePath, "r");
                if (file == NULL) {
                    printf("n/a\n");
                } else {
                    fseek(file, 0, SEEK_END);
                    long fileSize = ftell(file);
                    fseek(file, 0, SEEK_SET);

                    char *fileContents = (char *)malloc(fileSize + 1);
                    fread(fileContents, 1, fileSize, file);
                    fileContents[fileSize] = '\0';
                    fclose(file);

                    xor_encrypt(fileContents, key);

                    file = fopen(filePath, "w");
                    if (file == NULL) {
                        printf("n/a\n");
                    } else {
                        fprintf(file, "%s", fileContents);
                        fclose(file);
                    }

                    free(fileContents);
                }
            } else if (strstr(filename, ".h") != NULL) {
                char filePath[200];
                filePath[0] = '\0';  // Ensure the buffer is initially empty
                strcat(filePath, directoryPath);
                strcat(filePath, "/");
                strcat(filePath, filename);
                //                snprintf(filePath, sizeof(filePath), "%s/%s",
                //                directoryPath, filename);
                FILE *file = fopen(filePath, "w");
                if (file != NULL) {
                    fclose(file);
                }
            }
        }
    }

    closedir(dir);
}

int main() {
#ifdef LOG
    FILE *log_file = NULL;
    log_init("log.txt", &log_file);
#endif
    int choice = 0;
    char filename[100];
    char inputText[1000];
    char key[100];
    int shift;

    while (choice != -1) {
        int is_great_number = 1;
        if (scanf("%d", &choice) != 1) {
#ifdef LOG
            logcat(log_file, WARNING, "Wrong command");
#endif
            clear_input_buffer();
            printf("n/a\n");
            is_great_number = 0;
            continue;
        }
        switch (choice) {
            case 1:
                scanf("%s", filename);
#ifdef LOG
                logcat(log_file, INFO, "File opened");
#endif
                print_file_contents(filename);
#ifdef LOG
                logcat(log_file, INFO, "File contents printed");
#endif
                printf("\n");
                break;
            case 2:
                clear_input_buffer();
                fgets(inputText, sizeof(inputText), stdin);
                inputText[strcspn(inputText, "\n")] = '\0';
                FILE *checkFile = fopen(filename, "r");
                if (checkFile == NULL) {
                    printf("n/a\n");
#ifdef LOG
                    logcat(log_file, ERROR, "The file does not exist");
#endif
                } else {
                    fclose(checkFile);
                    append_to_file(filename, inputText);
#ifdef LOG
                    logcat(log_file, INFO, "The re-recording was successful");
#endif
                    print_file_contents(filename);
                    printf("\n");
                }
                break;
            case 3:
                clear_input_buffer();
                printf("Enter directory path: ");
                scanf("%s", filename);
#ifdef LOG
                logcat(log_file, INFO, "Directory processed for Caesar cipher and cleaning");
#endif
                printf("Enter Caesar cipher shift: ");
                if (scanf("%d", &shift) != 1) {
#ifdef LOG
                    logcat(log_file, ERROR, "The Caesar code was entered incorrectly");
#endif
                    clear_input_buffer();
                    printf("n/a\n");
                } else {
                    shift = shift % 26;
                    process_CFiles_in_directory(filename, shift);
#ifdef LOG
                    logcat(log_file, INFO, "The file is encoded with Caesar's code");
#endif
                }
                break;
            case 4:
                clear_input_buffer();
                printf("Enter directory path: ");
                scanf("%s", filename);
#ifdef LOG
                logcat(log_file, INFO, "Directory processed for Caesar cipher and cleaning");
#endif
                printf("Enter encryption key: ");
                scanf("%s", key);
#ifdef LOG
                logcat(log_file, DEBUG, "The encryption key has been successfully read");
#endif
                process_CFiles_in_directory_DES(filename, key);
#ifdef LOG
                logcat(log_file, INFO, "DES encryption successfully completed");
#endif
                break;
            case -1:
#ifdef LOG
                logcat(log_file, DEBUG, "The user entered -1");
#endif
                break;
            default:
                if (is_great_number) {
#ifdef LOG
                    logcat(log_file, WARNING, "The user entered something wrong");
#endif
                    clear_input_buffer();
                    printf("n/a\n");
                }
                break;
        }
    }
    return 0;
}
