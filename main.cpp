#include <iostream>
#include <windows.h>
#include <fileapi.h>
#include <chrono>

using namespace std;

void MenuPrint();
void MenuAttributesPrint();
int call;
VOID WINAPI FileIOCompletionRoutine(DWORD, DWORD, LPOVERLAPPED){
    call++;
}

int main() {
    int MenuPoint = 0;
    do {
        MenuPrint();
        cin>>MenuPoint;
        system("cls");
        switch (MenuPoint) {
            //Колличество дисков
            case 1: {
                cout << "Available Disk List:" << endl;
                //DWORD DiskAmount = GetLogicalDrives();
                //int n;
                for (int i = 0; i < 26; i++) {
                    //n = ((GetLogicalDrives() >> x) & 1);
                    if ((GetLogicalDrives() >> i) & 1) {
                        cout << "- " << (char) (65 + i) << ":\\" << endl;
                    }
                }
                system("pause");
            } break;
            //Информация о выбранном диске
            case 2: {
                cout << "Selected Disk Info" << endl;
                cout << "Enter Disk Name (For Example: c:\\): ";
                string DiskName;
                cin >> DiskName;
                cout << "Disk: ";
                switch(GetDriveType(DiskName.c_str())) {
                    case 0:
                        cout << "UNKNOWN" << endl; //Неизвестный тип
                        break;
                    case 1:
                        cout << "NO ROOT DIR" << endl; //Неправильный путь
                        break;
                    case 2:
                        cout << "REMOVABLE" << endl; //Съёмный диск
                        break;
                    case 3:
                        cout << "FIXED" << endl; //Фиксированный диск
                        break;
                    case 4:
                        cout << "REMOTE" << endl; //Удалённый диск
                        break;
                    case 5:
                        cout << "CDROM" << endl; //CD-ROM диск
                        break;
                    case 6:
                        cout << "RAMDISK" << endl; //RAM диск
                        break;
                }
                LPCSTR lpRootPathName = DiskName.c_str();
                char lpVolumeNameBuffer[MAX_PATH + 1];
                DWORD nVolumeNameSize = sizeof(lpVolumeNameBuffer);
                DWORD lpVolumeSerialNumber = 0;
                DWORD lpMaximumComponentLength = 0;
                DWORD lpFileSystemFlags = 0;
                char lpFileSystemNameBuffer[MAX_PATH + 1];
                DWORD nFileSystemNameSize = sizeof(lpFileSystemNameBuffer);
                if (!GetVolumeInformation(
                        lpRootPathName,
                        lpVolumeNameBuffer,
                        nVolumeNameSize,
                        &lpVolumeSerialNumber,
                        &lpMaximumComponentLength,
                        &lpFileSystemFlags,
                        lpFileSystemNameBuffer,
                        nFileSystemNameSize)) {
                    cout << "Error: failed to process request." << endl;
                }
                else {
                    cout << "Disk Name: " << lpVolumeNameBuffer << endl;
                    cout << "Serial Number: " << hex << lpVolumeSerialNumber << endl;
                    cout << "Max File Name Length (Symbols): " << dec << lpMaximumComponentLength << endl;
                    cout << "File System Options:" << endl;
                    //Указанный том поддерживает сохраненный регистр имен файлов при размещении имени на диске.
                    if (lpFileSystemFlags & FILE_CASE_PRESERVED_NAMES)
                        cout << " - The specified volume supports preserved case of file names when it places a name on disk." << endl;
                    //Указанный том поддерживает имена файлов с учетом регистра.
                    if (lpFileSystemFlags & FILE_CASE_SENSITIVE_SEARCH)
                        cout << " - The specified volume supports case-sensitive file names." << endl;
                    //Указанный том поддерживает сжатие файлов.
                    if (lpFileSystemFlags & FILE_FILE_COMPRESSION)
                        cout << " - The specified volume supports file-based compression." << endl;
                    //Указанный том поддерживает именованные потоки.
                    if (lpFileSystemFlags & FILE_NAMED_STREAMS)
                        cout << " - The specified volume supports named streams." << endl;
                    //Указанный том сохраняет и применяет списки управления доступом (ACL).
                    if (lpFileSystemFlags & FILE_PERSISTENT_ACLS)
                        cout << " - The specified volume preserves and enforces access control lists (ACL)." << endl;
                    //Указанный том доступен только для чтения.
                    if (lpFileSystemFlags & FILE_READ_ONLY_VOLUME)
                        cout << " - The specified volume is read-only." << endl;
                    //Указанный том поддерживает одну последовательную запись.
                    if (lpFileSystemFlags & FILE_SEQUENTIAL_WRITE_ONCE)
                        cout << " - The specified volume supports a single sequential write." << endl;
                   // Указанный том поддерживает зашифрованную файловую систему (EFS).
                    if (lpFileSystemFlags & FILE_SUPPORTS_ENCRYPTION)
                        cout << " - The specified volume supports the Encrypted File System (EFS)." << endl;
                    //Указанный том поддерживает расширенные атрибуты.
                    if (lpFileSystemFlags & FILE_SUPPORTS_EXTENDED_ATTRIBUTES)
                        cout << " - The specified volume supports extended attributes." << endl;
                    //Указанный том поддерживает жесткие ссылки.
                    if (lpFileSystemFlags & FILE_SUPPORTS_HARD_LINKS)
                        cout << " - The specified volume supports hard links." << endl;
                    //Указанный том поддерживает идентификаторы объектов.
                    if (lpFileSystemFlags & FILE_SUPPORTS_OBJECT_IDS)
                        cout << " - The specified volume supports object identifiers." << endl;
                    //Файловая система поддерживает открытие по FileID.
                    if (lpFileSystemFlags & FILE_SUPPORTS_OPEN_BY_FILE_ID)
                        cout << " - The file system supports open by FileID." << endl;
                    //Указанный том поддерживает точки повторного разбора.
                    if (lpFileSystemFlags & FILE_SUPPORTS_REPARSE_POINTS)
                        cout << " - The specified volume supports reparse points." << endl;
                    //Указанный том поддерживает разреженные файлы.
                    if (lpFileSystemFlags & FILE_SUPPORTS_SPARSE_FILES)
                        cout << " - The specified volume supports sparse files." << endl;
                    //Указанный том поддерживает транзакции.
                    if (lpFileSystemFlags & FILE_SUPPORTS_TRANSACTIONS)
                        cout << " - The specified volume supports transactions." << endl;
                    //Указанный том поддерживает журналы обновления порядковых номеров (USN).
                    if (lpFileSystemFlags & FILE_SUPPORTS_USN_JOURNAL)
                        cout << " - The specified volume supports update sequence number (USN) journals." << endl;
                    //Указанный том поддерживает Unicode в именах файлов по мере их появления на диске.
                    if (lpFileSystemFlags & FILE_UNICODE_ON_DISK)
                        cout << " - The specified volume supports Unicode in file names as they appear on disk." << endl;
                    //Указанный том является сжатым томом.
                    if (lpFileSystemFlags & FILE_VOLUME_IS_COMPRESSED)
                        cout << " - The specified volume is a compressed volume." << endl;
                    //Указанный том поддерживает дисковые квоты.
                    if (lpFileSystemFlags & FILE_VOLUME_QUOTAS)
                        cout << " - The specified volume supports disk quotas." << endl;
                    cout << "File System Name: " << lpFileSystemNameBuffer << endl;
                }
                DWORD lpSectorsPerCluster;
                DWORD lpBytesPerSector;
                DWORD lpNumberOfFreeClusters;
                DWORD lpTotalNumberOfClusters;
                if(GetDiskFreeSpace(
                        lpRootPathName,// имя диска(директории)
                        &lpSectorsPerCluster,
                        &lpBytesPerSector,
                        &lpNumberOfFreeClusters,
                        &lpTotalNumberOfClusters)) {
                    cout << "Sectors in Cluster: " << lpSectorsPerCluster << endl;
                    cout << "Byte in Sector: " << lpBytesPerSector << endl;
                    cout << "Free Clusters: "<< lpNumberOfFreeClusters << endl;
                    cout << "Max Clusters: " << lpTotalNumberOfClusters << endl;
                }
                system("pause");
            } break;
            //Создание или удаление директорий
            case 3: {
                int flag;
                string DiskName;
                cout << "Create or Remove Directory" << endl;
                cout << "Menu" << endl;
                cout << "1. Create Directory" << endl;
                cout << "2. Remove Directory" << endl;
                cout << "Enter Menu Point: ";
                cin >> flag;
                system("cls");
                cout << "Enter Directory Name (for example: c:\\folder): ";
                cin >> DiskName;
                switch (flag) {
                    //Создание директории
                    case 1:
                        if (!CreateDirectory(DiskName.c_str(), nullptr))
                            cout << "Error: failed to create directory." << endl;
                        else cout << "Directory Created." << endl;
                        break;
                    //Удаление директории
                    case 2:
                        if (!RemoveDirectory(DiskName.c_str()))
                            cout << "Error: the directory could not be deleted." << endl;
                        else cout << "Directory Deleted." << endl;
                        break;
                }
                system("pause");
            } break;
            //Создание файла в директории
            case 4: {
                cout << "Create File" << endl;
                cout << "Enter File Name (for example: c:\\folder\\1.txt): ";
                string DiskName;
                cin >> DiskName;
                if (CreateFile(
                        DiskName.c_str(),
                        GENERIC_WRITE | GENERIC_READ,
                        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                        nullptr,
                        CREATE_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        nullptr) == INVALID_HANDLE_VALUE)
                    cout << "Error " << GetLastError() << ": the file could not be created.";
                else cout << "File Created Successfully." << endl;
                system("pause");
            } break;
            //Копирование и перемещение файлов
            case 5: {
                cout << "Copy or Move File" << endl;
                cout << "Menu" << endl;
                cout << "1. Copy File" << endl;
                cout << "2. Move File" << endl;
                cout << "3. Move File (with verification)" << endl;
                cout << "Enter Menu Point: ";
                int flag;
                string DiskName1, DiskName2;
                cin >> flag;
                system("cls");
                switch (flag) {
                    case 1: {
                        cout << "Enter the name of the source file (for example: c:\\folder\\1.txt): ";
                        cin >> DiskName1;
                        cout << "Enter the name of the copy file: ";
                        cin >> DiskName2;
                        if (CopyFile(
                                DiskName1.c_str(),
                                DiskName2.c_str(),
                                false))
                            cout << "The file was copied successfully." << endl;
                        else
                            cout << "Error " << GetLastError() << ": Failed to copy file." << endl;
                    } break;
                    case 2: {
                        cout << "Enter File Name (foe example: c:\\folder\\1.txt): ";
                        cin >> DiskName1;
                        cout << "Enter destination address (for example: c:\\folder\\1.txt): ";
                        cin >> DiskName2;
                        if (MoveFile(DiskName1.c_str(), DiskName2.c_str()))
                            cout << "File moved successfully." << endl;
                        else
                            cout << "Error  " << GetLastError() << ": Failed to move file." << endl;
                        system("pause");
                    } break;
                    case 3: {
                        cout << "Enter File Name (for example: c:\\1.txt): ";
                        cin >> DiskName1;
                        cout << "Enter destination address (for example: c:\\folder\\1.txt): ";
                        cin >> DiskName2;
                        int moveFileEx_temp = 0;
                        if (MoveFileEx(DiskName1.c_str(), DiskName2.c_str(), NULL))
                            cout << "File or directory moved successfully." << endl;
                        else if (GetLastError() == 183) {
                            cout << "Such a file already exists in this directory. Replace?" << endl;
                            cout << "1 - Yes/0 - No: ";
                            cin >> moveFileEx_temp;
                            system("cls");
                            if (moveFileEx_temp)
                                if (MoveFileEx(
                                        DiskName1.c_str(),
                                        DiskName2.c_str(),
                                        MOVEFILE_REPLACE_EXISTING))
                                    cout << "File or directory moved successfully!" << endl;
                                else
                                    cout << "Error " << GetLastError() << ": failed to move file." << endl;
                        }
                        else
                            cout << "Error " << GetLastError() << ": failed to move file." << endl;
                    } break;
                }
                system("pause");
            } break;
            //Анализ и изменение атрибутов файлов
            case 6: {
                cout << "Analyse and Change Attributes" << endl;
                MenuAttributesPrint();
                cout << "Enter Menu Point: ";
                int flag;
                string DiskName;
                FILETIME TimeCreate, TimeLastAccess, TimeLastWrite, FileTime;
                SYSTEMTIME Time, SystemTime;
                cin >> flag;
                system("cls");
                switch (flag) {
                    case 1: {
                        cout << "Enter file name (for example: c:\\folder\\1.txt): ";
                        cin >> DiskName;
                        DWORD attribute = GetFileAttributes(DiskName.c_str());
                        if (attribute == 0)
                            cout << "Error: failed to get file attributes." << endl;
                        else if (attribute == -1)
                            cout << "Error: file not found." << endl;
                        else {
                            cout << "File Attribute (" << attribute << "):" << endl;
                            switch(attribute) {
                                case FILE_ATTRIBUTE_ARCHIVE:
                                    cout << " - Archive file" << endl; //Архивный файл
                                    break;
                                case FILE_ATTRIBUTE_COMPRESSED:
                                    cout << " - Compressed file" << endl; //Сжатый файл
                                    break;
                                case FILE_ATTRIBUTE_DIRECTORY:
                                    cout << " - Catalog" << endl; //Каталог
                                    break;
                                case FILE_ATTRIBUTE_HIDDEN:
                                    cout << " - Hidden file or directory" << endl; //Скрытый файл или каталог
                                    break;
                                case FILE_ATTRIBUTE_NORMAL:
                                    cout << " - File has no attributes" << endl; //Файл не имеет атрибутов
                                    break;
                                case FILE_ATTRIBUTE_READONLY:
                                    cout << " - Read-only file" << endl; //Файл только для чтения
                                    break;
                                default:
                                    break;
                            }
                        }
                        system("pause");
                    } break;
                    case 2: {
                        cout << "Enter File Name (for example: c:\\folder\\1.txt): ";
                        cin >> DiskName;
                        cout << "Change file attribute to:" << endl;
                        cout << "1. Archive file" << endl;
                        cout << "2. Hidden file" << endl;
                        cout << "3. File without attributes" << endl;
                        cout << "4. Read-only file" << endl;
                        cout << "5. System file" << endl;
                        cout << "Enter Menu Point: ";
                        int SetAttr;
                        cin >> SetAttr;
                        system("cls");
                        switch (SetAttr) {
                            case 1:
                                if (SetFileAttributes(DiskName.c_str(), FILE_ATTRIBUTE_ARCHIVE))
                                    cout << "File attribute changed successfully" << endl;
                                else
                                    cout << "Error " << GetLastError() << endl;
                                break;
                            case 2:
                                if (SetFileAttributes(DiskName.c_str(), FILE_ATTRIBUTE_HIDDEN))
                                    cout << "File attribute changed successfully" << endl;
                                else
                                    cout << "Error " << GetLastError() << endl;
                                break;
                            case 3:
                                if (SetFileAttributes(DiskName.c_str(), FILE_ATTRIBUTE_NORMAL))
                                    cout << "File attribute changed successfully" << endl;
                                else
                                    cout << "Error " << GetLastError() << endl;
                                break;
                            case 4:
                                if (SetFileAttributes(DiskName.c_str(), FILE_ATTRIBUTE_READONLY))
                                    cout << "File attribute changed successfully" << endl;
                                else
                                    cout << "Error " << GetLastError() << endl;
                                break;
                            case 5:
                                if (SetFileAttributes(DiskName.c_str(), FILE_ATTRIBUTE_SYSTEM))
                                    cout << "File attribute changed successfully" << endl;
                                else
                                    cout << "Error " << GetLastError() << endl;
                                break;
                        }
                        system("pause");
                    } break;
                    case 3: {
                        long handleInfo, FileAttributes;
                        BY_HANDLE_FILE_INFORMATION infoFile;
                        HANDLE handleFile;
                        cout << "Enter File Name (for example: c:\\folder\\1.txt): ";
                        cin >> DiskName;
                        handleFile = CreateFileA(
                                (LPCSTR) DiskName.c_str(),
                                GENERIC_READ,
                                FILE_SHARE_READ,
                                NULL,
                                OPEN_EXISTING,
                                0,
                                NULL);
                        handleInfo = GetFileInformationByHandle(handleFile, &infoFile);
                        if (!handleInfo)
                            cout << "Error " << GetLastError() << endl;
                        else {
                            FileAttributes = infoFile.dwFileAttributes;
                            if (FileAttributes == -1)
                                cout << "File " << DiskName << " not found." << endl;
                            else {
                                cout << "File information by descriptor:" << endl;
                                if (FileAttributes & FILE_ATTRIBUTE_ARCHIVE)
                                    cout << "File " << DiskName << " - archival." << endl; //архивный
                                if (FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                                    cout << "File " << DiskName << " - directory." << endl; //директория
                                if (FileAttributes & FILE_ATTRIBUTE_READONLY)
                                    cout << "File " << DiskName << " - read-only." << endl;
                                if (FileAttributes & FILE_ATTRIBUTE_SYSTEM)
                                    cout << "File " << DiskName << " - system." << endl;
                                if (FileAttributes & FILE_ATTRIBUTE_COMPRESSED)
                                    cout << "File " << DiskName << " - compressed." << endl; //сжатый
                                if (FileAttributes & FILE_ATTRIBUTE_HIDDEN)
                                    cout << "File " << DiskName << " - hidden." << endl; //скрытый
                                if (FileAttributes & FILE_ATTRIBUTE_NORMAL)
                                    cout << "File " << DiskName << " does not have such attributes.";
                                if (FileAttributes == 0)
                                    cout << "Error " << GetLastError() << endl;
                            }
                            cout << "File Index High: " << infoFile.nFileIndexHigh << endl;
                            cout << "Volume Serial Number: " << infoFile.dwVolumeSerialNumber << endl;
                            cout << "File Size High: " << infoFile.nFileSizeHigh << endl;
                            cout << "File Size Low: " << infoFile.nFileSizeLow << endl;
                            cout << "Number of Links: " << infoFile.nNumberOfLinks << endl;
                            cout << "File Index Low: " << infoFile.nFileIndexLow << endl;
                        }
                        handleInfo = CloseHandle(handleFile);
                        cout << endl;
                        system("pause");
                    } break;
                    case 4: {
                        cout << "Enter File Name (for example: c:\\folder\\1.txt): ";
                        cin >> DiskName;
                        HANDLE File = CreateFileA(
                                DiskName.c_str(),
                                GENERIC_READ | GENERIC_WRITE,
                                FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
                                nullptr,
                                CREATE_ALWAYS,
                                FILE_ATTRIBUTE_NORMAL,
                                nullptr);
                        if (GetFileTime(
                                File,
                                &TimeCreate,
                                &TimeLastAccess,
                                &TimeLastWrite)) {
                            FileTimeToSystemTime(&TimeCreate, &Time);
                            cout << "File creation date and time: " <<
                                 Time.wYear << "/" << Time.wMonth << "/"
                                 << Time.wDay << "   " << Time.wHour + 3 << ":" <<
                                 Time.wMinute << ":" << Time.wSecond << endl;
                            FileTimeToSystemTime(&TimeLastAccess, &Time);
                            cout << "Date and time of the last access to the file: " <<
                                 Time.wYear << "/" << Time.wMonth << "/"
                                 << Time.wDay << "   " << Time.wHour + 3 << ":" <<
                                 Time.wMinute << ":" << Time.wSecond << endl;
                            FileTimeToSystemTime(&TimeLastWrite, &Time);
                            cout << "Date and time of the last modification of the file: " <<
                                 Time.wYear << "/" << Time.wMonth << "/"
                                 << Time.wDay << "   " << Time.wHour + 3 << ":" <<
                                 Time.wMinute << ":" << Time.wSecond << endl;
                        }
                        else
                            cout << "Error " << GetLastError() << ": failed to get file information" << endl;
                        system("pause");
                    } break;
                    case 5: {
                        cout << "Enter File Name (for example: c:\\folder\\1.txt): ";
                        cin >> DiskName;
                        HANDLE File = CreateFileA(
                                DiskName.c_str(),
                                GENERIC_READ | GENERIC_WRITE,
                                FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
                                nullptr,
                                CREATE_ALWAYS,
                                FILE_ATTRIBUTE_NORMAL,
                                nullptr);
                        GetSystemTime(&SystemTime);
                        SystemTimeToFileTime(&SystemTime, &FileTime);
                        if (SetFileTime(
                                File,
                                &FileTime,
                                &FileTime,
                                &FileTime))
                            cout << "Time attributes replaced successfully!" << endl;
                        else
                            cout << "Error " << GetLastError() << endl;
                        system("pause");
                    } break;
                }
            } break;
            //Перекрывание
            case 7: {
                cout << "Enter Readable File Name (for example: c:\\1.txt): ";
                string DiskName;
                long long FileSize;
                cin >> DiskName;
                HANDLE Read, Write;
                Read = CreateFile(
                        DiskName.c_str(),
                        GENERIC_READ | GENERIC_WRITE,
                        0,
                        nullptr,
                        OPEN_EXISTING, //Открывает файл или устройство, только если оно существует.
                        FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING,
                        nullptr);
                if (Read == INVALID_HANDLE_VALUE)
                    cout << "Error" << endl;
                else {
                    cout << "Enter Writeable File Name (for example: c:\\1.txt): ";
                    cin >> DiskName;
                    Write = CreateFile(
                            DiskName.c_str(),
                            GENERIC_READ | GENERIC_WRITE,
                            0,
                            nullptr,
                            CREATE_ALWAYS, //Всегда открывает файл.
                            FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING,
                            nullptr);
                    if (Write == INVALID_HANDLE_VALUE)
                        cout << "Error" << endl;
                    else {
                        cout << "Enter Byte Count: ";
                        int ByteCount;
                        cin >> ByteCount;
                        cout << "Enter Operation Count: ";
                        int OperationCount;
                        cin >> OperationCount;
                        FileSize = GetFileSize(Read, nullptr);
                        OVERLAPPED *ReadOver;
                        char **BuffOver = new char *[OperationCount]();
                        ReadOver = new OVERLAPPED[OperationCount]();
                        OVERLAPPED over{0};
                        for (int i = 0; i < OperationCount; i++) {
                            ReadOver[i] = over;
                            over.Offset += ByteCount;
                            BuffOver[i] = new char[ByteCount]();
                        }
                        auto begin = chrono::system_clock::now();
                        for (; FileSize > 0;) {
                            call = 0;
                            for (int i = 0; i < OperationCount; i++)
                                ReadFileEx(
                                        Read,
                                        BuffOver[i],
                                        ByteCount,
                                        &ReadOver[i],
                                        FileIOCompletionRoutine);
                            for (; call < OperationCount;)
                                SleepEx(INFINITE, true);
                            call = 0;
                            for (int i = 0; i < OperationCount; i++)
                                WriteFileEx(
                                        Write,
                                        BuffOver[i],
                                        ByteCount,
                                        &ReadOver[i],
                                        FileIOCompletionRoutine);
                            for (; call < OperationCount;)
                                SleepEx(INFINITE, true);
                            for (int i = 0; i < OperationCount; i++)
                                ReadOver[i].Offset += OperationCount * ByteCount;
                            FileSize -= OperationCount * ByteCount;
                            auto end = chrono::system_clock::now();
                            cout << "Time - " <<  chrono::duration_cast<chrono::milliseconds>(end - begin).count() << endl;
                            FileSize = GetFileSize(Read, nullptr);
                            SetFilePointer(Write, FileSize, nullptr, FILE_BEGIN);
                            SetEndOfFile(Write);
                            delete [] ReadOver;
                            for(int i = 0; i < OperationCount; i++)
                                delete [] BuffOver[i];
                            delete [] BuffOver;
                        }
                    }
                    CloseHandle(Write);
                }
                CloseHandle(Read);
                system("pause");
            } break;
            default:
                break;
        }
    } while(MenuPoint != 8);
    return 0;
}

void MenuPrint() {
    system("cls");
    cout << "Menu" << endl;
    cout << "1. Disk List" << endl;
    cout << "2. Selected Disk Info" << endl;
    cout << "3. Create or Remove Directory" << endl;
    cout << "4. Create File" << endl;
    cout << "5. Copy or Move File" << endl;
    cout << "6. Analyse and Change Attributes" << endl;
    cout << "7. Overlapped" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter Menu Point: ";
}

void MenuAttributesPrint() {
    cout << "1. Displaying information about attributes" << endl;
    cout << "2. Changing attribute information" << endl;
    cout << "3. Displaying information about a file by descriptor" << endl;
    cout << "4. System time information" << endl;
    cout << "5. System time change" << endl;
}
