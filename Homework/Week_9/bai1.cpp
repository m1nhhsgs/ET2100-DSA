#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Cấu trúc lưu thông tin về file
typedef struct File {
    char name[100];
    long size;
    time_t creationTime;
    struct File *next;
} File;

typedef struct Folder {
    File *first;
    File *last;
} Folder;

// Khởi tạo folder
void initializeFolder(Folder *folder) {
    folder->first = folder->last = NULL;
}

// Tạo file mới
File* createFile(const char *name, long size, time_t creationTime) {
    File *file = (File*)malloc(sizeof(File));
    strcpy(file->name, name);
    file->size = size;
    file->creationTime = creationTime;
    file->next = NULL;
    return file;
}

// Thêm file vào folder
void addFile(Folder *folder, const char *name, long size, time_t creationTime) {
    File *file = createFile(name, size, creationTime);
    if (folder->first == NULL) {
        folder->first = folder->last = file;
    } else {
        folder->last->next = file;
        folder->last = file;
    }
}

// Nhập thông tin file
void inputFileInfo(Folder *folder) {
    int n;
    printf("Enter the number of files: ");
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        char name[100];
        long size;
        time_t creationTime;
        printf("Enter file name: ");
        scanf("%s", name);
        printf("Enter file size (bytes): ");
        scanf("%ld", &size);
        printf("Enter file creation time (epoch time): ");
        scanf("%ld", &creationTime);
        addFile(folder, name, size, creationTime);
    }
}

// Sắp xếp file theo dung lượng tăng dần
void sortFiles(Folder *folder) {
    if (folder->first == NULL) return;

    for (File *i = folder->first; i != NULL; i = i->next) {
        for (File *j = i->next; j != NULL; j = j->next) {
            if (i->size > j->size) {
                char tempName[100];
                long tempSize;
                time_t tempCreationTime;

                strcpy(tempName, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, tempName);

                tempSize = i->size;
                i->size = j->size;
                j->size = tempSize;

                tempCreationTime = i->creationTime;
                i->creationTime = j->creationTime;
                j->creationTime = tempCreationTime;
            }
        }
    }
}

// Xóa file có dung lượng bé nhất
void deleteFile(Folder *folder) {
    if (folder->first == NULL) return;

    // Tìm dung lượng bé nhất
    long minSize = folder->first->size;
    for (File *file = folder->first; file != NULL; file = file->next) {
        if (file->size < minSize) {
            minSize = file->size;
        }
    }
    File *prev = NULL;
    File *current = folder->first;
    while (current != NULL) {
        if (current->size == minSize) {
            if (prev == NULL) { 
                folder->first = current->next;
                free(current);
                current = folder->first;
            } else { 
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
    folder->last = prev;
}

// In danh sách file
void printFileList(const Folder *folder) {
    for (File *file = folder->first; file != NULL; file = file->next) {
        printf("File name: %s, Size: %ld bytes, Creation time: %ld\n", file->name, file->size, file->creationTime);
    }
}

int main() {
    Folder folder;
    initializeFolder(&folder);
    inputFileInfo(&folder);

    sortFiles(&folder);
    printf("\nFile list after sorting by size in ascending order:\n");
    printFileList(&folder);
    deleteFile(&folder);
    printf("\nFile list after deleting files with the smallest size:\n");
    printFileList(&folder);
    return 0;
}