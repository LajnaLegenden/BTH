#include "fs.h"
#include <cstdlib>  // For the realpath function
#include <unistd.h> // For the chdir function
#include <iomanip>
#include <iostream>
#include <cassert>
#include <array>
#include <string>
#include <cstring>
#include <vector>
#include <memory>
#include <algorithm>
#include <cctype>
#include <locale>

// helpers
std::vector<std::string> splitString(const std::string &str, char delimiter)
{
    std::vector<std::string> parts;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos)
    {
        parts.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }

    parts.push_back(str.substr(start));

    return parts;
}
// removes filename from full path
std::string cutFileName(std::string path)
{
    std::string delimiter = "/";
    size_t pos = path.find_last_of(delimiter);
    return path.substr(0, pos);
}

std::string joinVector(const std::vector<std::string> &vec, const std::string &delimiter)
{
    std::string result;

    for (size_t i = 0; i < vec.size(); ++i)
    {
        result += vec[i];
        if (i < vec.size() - 1)
        {
            result += delimiter;
        }
    }

    return result;
}

static inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                    { return !std::isspace(ch); }));
}

// trim from end (in place)
static inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                         { return !std::isspace(ch); })
                .base(),
            s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s)
{
    rtrim(s);
    ltrim(s);
}

std::string exec(const char *cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result;
}

std::string absolutePath(std::string pwd, std::string path)
{

    std::string command = "realpath -m --relative-to=/ " + pwd + "/" + path;
    std::string result = exec(command.c_str());
    trim(result);
    return "/" + result;
}

FS::FS()
{
    std::cout << "FS::FS()... Creating file system\n";
    this->currentDir = "/";
    currDir = ROOT_BLOCK;
    srand(time(NULL));

    // read fat
    this->disk.read(FAT_BLOCK, (uint8_t *)fat);
}

FS::~FS()
{
}

bool FS::doesFileExistInFolder(int block, std::string name)
{
    dir_entry dir[BLOCK_SIZE];
    this->disk.read(block, (uint8_t *)dir);

    for (int i = 0; i < BLOCK_SIZE / sizeof(dir_entry); i++)
    {
        if (dir[i].type == TYPE_FILE)
        {
            if (dir[i].file_name == name)
            {
                return true;
            }
        }
    }
    return false;
}

// formats the disk, i.e., creates an empty file system
int FS::format()
{

    std::cout << "FS::format()\n";
    // print sizeof dir_entry
    //  init fat
    this->fat[ROOT_BLOCK] = FAT_EOF;
    this->fat[FAT_BLOCK] = FAT_EOF;
    for (int i = 2; i < BLOCK_SIZE / 2; i++)
    {
        this->fat[i] = FAT_FREE;
    }

    // zero out the entire disk
    int zeros[BLOCK_SIZE];
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        zeros[i] = 0;
    }
    for (int i = 0; i < BLOCK_SIZE / 2; i++)
    {
        this->disk.write(i, (uint8_t *)zeros);
    }

    // create empty root
    dir_entry root[BLOCK_SIZE];
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        root[i].size = 0;
        root[i].first_blk = 0;
        root[i].type = 0;
        root[i].access_rights = 0;
    }

    // clear disk
    for (int idx = 2; idx < BLOCK_SIZE / 2; idx++)
    {
        uint8_t emptyBlock[BLOCK_SIZE];
        std::memset(emptyBlock, 0, BLOCK_SIZE);
        disk.write(idx, (uint8_t *)emptyBlock);
    }

    // Write root to disk
    this->disk.write(ROOT_BLOCK, (uint8_t *)root);
    // Save fat to disk
    this->disk.write(FAT_BLOCK, (uint8_t *)fat);

    currDir = ROOT_BLOCK;
    currentDir = "/";
    std::cout << "sizeof dir_entry: " << sizeof(dir_entry) << "\n";

    return 0;
}

int FS::create(std::string filepath)
{
    // check if file path is to long
    if (filepath.length() > 56)
    {
        std::cout << "FS::create - ERROR: File path is to long\n";
        return -1;
    }
    this->log("getting file name");

    std::string absPathToFile = absolutePath(currentDir, filepath);

    std::string name = getFileName(filepath);

    absPathToFile = cutFileName(absPathToFile);

    this->log("name is " + name);
    this->log("path is " + absPathToFile);

    // FIXME check duplicate file name
    if (doesFileExistInFolder(currDir, name))
    {
        std::cout << "FS::create - ERROR: File already exists\n";
        return -1;
    }

    // get input from line
    std::string input;
    std::string data;
    std::getline(std::cin, input);

    while (input != "")
    {
        data += input + "\n";
        std::getline(std::cin, input);
    }

    int code = writeFile(data, name, absPathToFile);

    return code;
}

/// @brief
/// @param path aboulute path path to a FOLDER
/// @return id of the block the folder is stored on
int FS::getDirBlock(std::string path)
{
    int b_currDir = currDir;
    if (path.empty())
    {
        return ROOT_BLOCK;
    }

    // check if path is absolute
    if (path[0] == '/')
    {
        b_currDir = ROOT_BLOCK;
        path.erase(0, 1);
    }

    // split path into vector
    std::vector<std::string> pathVector;

    std::string delimiter = "/";
    size_t pos = 0;
    std::string token;
    while ((pos = path.find(delimiter)) != std::string::npos)
    {
        token = path.substr(0, pos);
        pathVector.push_back(token);
        path.erase(0, pos + delimiter.length());
    }

    if (path.find(delimiter) == std::string::npos)
    {
        pathVector.push_back(path);
    }

    // loop through path
    for (std::string s : pathVector)
    {
        // read current dir
        dir_entry dir[BLOCK_SIZE];
        this->disk.read(b_currDir, (uint8_t *)dir);

        // loop through dir
        for (int i = 0; i < BLOCK_SIZE; i++)
        {
            // check if file is not empty
            if (&dir[i].size != 0)
            {
                // check if file is a dir
                if (dir[i].type == TYPE_DIR)
                {
                    // check if file name matches
                    if (dir[i].file_name == s)
                    {
                        // set current dir to file block
                        b_currDir = dir[i].first_blk;
                        break;
                    }
                }
            }
        }
    }
    return b_currDir;
}

void FS::saveFat()
{
    this->disk.write(FAT_BLOCK, (uint8_t *)fat);
}

void FS::log(std::string msg)
{
    printf("FS::log - %s\n", msg.c_str());
}

void FS::saveDirEntry(int16_t block, dir_entry entry)
{
    this->disk.write(block, (uint8_t *)&entry);
}

int FS::findFreeFatBlock()
{
    // Finds a free block in the FAT
    int16_t free_block = 0;
    while (this->fat[free_block] != FAT_FREE)
    {
        // Check if we are at the end of the FAT
        if (free_block == BLOCK_SIZE / 2)
        {
            std::cout << "FS::findFreeFatBlock - ERROR: No free blocks\n";
            return -1;
        }

        free_block++;
    }
    this->log("Found free block at " + std::to_string(free_block));
    return free_block;
}

int FS::findSpotInFolder(dir_entry *dir)
{
    // std::cout << BLOCK_SIZE / sizeof(dir_entry) << "\n";
    for (int i = 0; i < BLOCK_SIZE / sizeof(dir_entry); i++)
    {
        dir_entry entry = dir[i];
        if (entry.type == TYPE_DIR)
            continue;

        if (entry.size != 0)
            continue;

        return i;
    }
    return -1;
}
int FS::resolve(std::string originalPath, bool canBeFolder, std::string &name, std::string &path)
{
    // check if originalPath has any slashes
    if (originalPath.find('/') == std::string::npos)
    {
        // no slashes, so originalPath is just a name
        name = originalPath;
        if (currDir == ROOT_BLOCK)
            path = "/";
        else
            path = currentDir + "/";

        return 0;
    }

    // check if originalPath is absolute
    if (originalPath[0] == '/')
    {
        name = getFileName(originalPath);
        path = cutFileName(originalPath) + "/";
        if (!canBeFolder)
            return 0;

        int pathBlock = ROOT_BLOCK;
        auto parts = splitString(path, '/');

        for (std::string part : parts)
        {
            if (part == "")
                continue;

            dir_entry dir[BLOCK_SIZE];
            this->disk.read(pathBlock, (uint8_t *)dir);

            for (int i = 0; i < BLOCK_SIZE / sizeof(dir_entry); i++)
            {
                if (dir[i].file_name == part)
                {
                    if (dir[i].type == TYPE_DIR)
                    {
                        pathBlock = dir[i].first_blk;
                        break;
                    }
                }
            }
        }
    }

    log("original path is " + originalPath);

    if (canBeFolder)
    {
        if (originalPath[originalPath.length() - 1] == '/')
        {
            name = "";
            path = absolutePath(currentDir, originalPath);
            return 0;
        }

        // oath ../asd/d where d is a directroy

        name = getFileName(originalPath);
        path = cutFileName(originalPath);
        if (path == "..")
            path = "../";

        path = absolutePath(currentDir, path);
        int dirBlock = getDirBlock(path);
        if (dirBlock == -1)
            return -1;

        dir_entry dir[BLOCK_SIZE];
        this->disk.read(dirBlock, (uint8_t *)dir);

        for (int i = 0; i < BLOCK_SIZE / sizeof(dir_entry); i++)
        {
            if (dir[i].file_name == name)
            {
                if (dir[i].type == TYPE_DIR)
                {
                    path = absolutePath(path, name);
                    name = "";
                    return 0;
                }
            }
        }
        return -1;
    }
    else
    {
        name = getFileName(originalPath);
        path = cutFileName(originalPath);
        if (path == "..")
            path = "../";
        path = absolutePath(currentDir, path);
        // if last char is . then remove it
        if (path[path.length() - 1] == '.')
        {
            path = path.substr(0, path.length() - 1);
        }
        return 0;
    }

    return 0;
}

// cat <filepath> reads the content of a file and prints it on the screen
int FS::cat(std::string filepath)
{
    std::cout << "FS::cat(" << filepath << ")\n";

    std::string name;
    std::string dir;

    int pathOp = resolve(filepath, false, name, dir);

    if (pathOp == -1)
    {
        std::cout << "FS::cat - ERROR: Path resolved failed\n";
        return -1;
    }

    std::string file = readFile(dir, name);

    if (file == "ERR_FILENOTFOUND")
    {
        std::cout << "FS::cat - ERROR: File not found\n";
        return -1;
    }
    if (file == "ERR_NOFILE")
    {
        std::cout << "FS::cat - ERROR: File is not a file\n";
        return -1;
    }
    if (file == "ERR_NOACCESS")
    {
        std::cout << "FS::cat - ERROR: No read access\n";
        return -1;
    }

    std::cout << file << std::endl;
    return 0;
}

std::string FS::readFile(std::string dir, std::string file)
{
    std::cout << "FS::readFile(" << dir << file << ")\n";
    int dirBlock = getDirBlock(dir);
    log("dir block is " + std::to_string(dirBlock));
    dir_entry dirEntries[BLOCK_SIZE];
    this->disk.read(dirBlock, (uint8_t *)dirEntries);
    int fileBlock = -1;
    int metadatapos = -1;
    // loop through dir
    for (int i = 0; i < BLOCK_SIZE / sizeof(dir_entry); i++)
    {
        // check if file is not empty
        if (&dirEntries[i].size != 0)
        {
            // check if file is a dir
            if (dirEntries[i].type == TYPE_FILE)
            {
                // check if file name matches
                if (dirEntries[i].file_name == file)
                {
                    log("found file");
                    metadatapos = i;
                    fileBlock = dirEntries[i].first_blk;
                    break;
                }
            }
        }
    }

    if (fileBlock == -1)
        return "ERR_FILENOTFOUND";

    if (dirEntries[metadatapos].access_rights & READ)
    {
        log("has read access");
        log("file block is " + std::to_string(dirEntries[metadatapos].access_rights));
    }
    else
    {
        return "ERR_NOACCESS";
    }

    if (dirEntries[metadatapos].type != TYPE_FILE)
    {
        std::cout << "FS::cat - ERROR: File is not a file\n";
        return "ERR_NOFILE";
    }

    std::string stringFile;
    char data[BLOCK_SIZE];
    while (fileBlock != FAT_EOF)
    {
        this->disk.read(fileBlock, (uint8_t *)data);
        stringFile += data;
        fileBlock = this->fat[fileBlock];
    }
    return stringFile;
}

// ls lists the content in the currect directory (files and sub-directories)
int FS::ls()
{
    // log current dir and currdir
    log("current dir is " + currentDir);
    log("currDir is " + std::to_string(currDir));

    printf("%-8s %-8s %-8s %-8s\n", "name", "size", "type", "permissions");

    dir_entry dir[BLOCK_SIZE];
    this->disk.read(currDir, (uint8_t *)dir);

    if (currDir != ROOT_BLOCK)
    {

        int parentDirBlock = getDirBlock(absolutePath(currentDir, "../"));

        // find currentdir in parent dir
        dir_entry parentDir[BLOCK_SIZE];
        this->disk.read(parentDirBlock, (uint8_t *)parentDir);
        int currentDirPos = -1;
        for (int i = 0; i < BLOCK_SIZE / sizeof(dir_entry); i++)
        {
            if (parentDir[i].type == TYPE_DIR)
            {
                if (parentDir[i].first_blk == currDir)
                {
                    currentDirPos = i;
                    break;
                }
            }
        }

        // check if we have read access to current dir
        if (parentDir[currentDirPos].access_rights & READ)
        {
            log("has read access");
        }
        else
        {
            std::cout << "FS::ls - ERROR: No read access\n";
            return -1;
        }
    }

    for (int i = 0; i < BLOCK_SIZE / sizeof(dir_entry); i++)
    {
        dir_entry entry = dir[i];
        if ((entry.type <= TYPE_FILE && entry.size <= 0) || (entry.type >= TYPE_DIR && entry.size == 0))
        {
            continue;
        }

        if (dir[i].size != 0)
        {
            std::string type = "file";
            std::string size = std::to_string(dir[i].size);
            if (dir[i].type == TYPE_DIR)
            {
                type = "dir";
                size = "-";
            }
            printf("%-8s %-8s %-8s %-8s\n", dir[i].file_name, size.c_str(), type.c_str(), permissions[dir[i].access_rights].c_str());
        }
    }

    return 0;
}

// cp <sourcepath> <destpath> makes an exact copy of the file
// <sourcepath> to a new file <destpath>
int FS::cp(std::string sourcepath, std::string destpath)
{
    std::cout << "FS::cp(" << sourcepath << "," << destpath << ")\n";

    std::string sourceName;
    std::string sourcePath;

    int ret = resolve(sourcepath, false, sourceName, sourcePath);

    std::string destName;
    std::string destPath;

    ret = resolve(destpath, true, destName, destPath);

    if (destName.empty())
    {
        log("dest name is empty, must be a folder");
        destName = sourceName;
    }
    else
    {
        destPath = cutFileName(destPath);
    }

    int destDirBlock = getDirBlock(destPath);

    if (destDirBlock == -1)
        return -1;

    // check if destName already exists as a folder

    dir_entry destDir[BLOCK_SIZE];
    this->disk.read(destDirBlock, (uint8_t *)destDir);

    for (int i = 0; i < BLOCK_SIZE / sizeof(dir_entry); i++)
    {
        if (destDir[i].type == TYPE_DIR)
        {
            if (destDir[i].file_name == destName)
            {
                log("dest name already exists as a folder, so put it inside the file");
                destPath += destName + "/";
                destName = sourceName;
                break;
            }
        }
        else
        {
            // prtin destfile exists

            printf("dest file exists\n");
            return -1;
        }
    }

    // log source and dest
    log("source name is " + sourceName);
    log("source dir is " + sourcePath);
    log("dest name is " + destName);
    log("dest dir is " + destPath);

    int sourceDirBlock = getDirBlock(sourcePath);
    dir_entry sourceDirEntries[BLOCK_SIZE];
    this->disk.read(sourceDirBlock, (uint8_t *)sourceDirEntries);
    int fileBlock = -1;
    int metadatapos = -1;
    // loop through dir
    for (int i = 0; i < BLOCK_SIZE / sizeof(dir_entry); i++)
    {
        // check if file is not empty
        if (&sourceDirEntries[i].size != 0)
        {
            // check if file is a dir
            if (sourceDirEntries[i].type == TYPE_FILE)
            {
                // check if file name matches
                if (sourceDirEntries[i].file_name == sourceName)
                {
                    log("found file");
                    fileBlock = sourceDirEntries[i].first_blk;
                    metadatapos = i;
                    break;
                }
            }
        }
    }

    if (fileBlock == -1)
        return -1;

    // read file
    dir_entry file = sourceDirEntries[metadatapos];

    if (file.type != TYPE_FILE)
    {
        std::cout << "FS::cp - ERROR: File is a folder\n";
        return -1;
    }

    if (file.access_rights & READ == 0)
    {
        std::cout << "FS::cp - ERROR: No read access\n";
        return -1;
    }

    std::string data = readFile(sourcePath, sourceName);

    // write string to new file
    writeFile(data, destName, destPath);

    return 0;
}

// mv <sourcepath> <destpath> renames the file <sourcepath> to the name <destpath>,
// or moves the file <sourcepath> to the directory <destpath> (if dest is a directory)
int FS::mv(std::string sourcepath, std::string destpath)
{
    std::cout << "FS::mv(" << sourcepath << "," << destpath << ")\n";

    std::string sourceName;
    std::string sourcePath;

    int ret = resolve(sourcepath, false, sourceName, sourcePath);

    std::string destName;
    std::string destPath;

    ret = resolve(destpath, true, destName, destPath);

    if (destName.empty())
    {
        log("dest name is empty, must be a folder");
        destName = sourceName;
    }

    int destDirBlock = getDirBlock(destPath);

    if (destDirBlock == -1)
        return -1;

    // check if destName already exists as a folder

    dir_entry destDir[BLOCK_SIZE];
    this->disk.read(destDirBlock, (uint8_t *)destDir);

    for (int i = 0; i < BLOCK_SIZE / sizeof(dir_entry); i++)
    {
        if (destDir[i].type == TYPE_DIR)
        {
            if (destDir[i].file_name == destName)
            {
                log("dest name already exists as a folder, so put it inside the file");
                destPath += destName + "/";
                destName = sourceName;
                break;
            }
        }
        else
        {
            // prtin destfile exists

            printf("dest file exists\n");
            return -1;
        }
    }

    // log source and dest
    log("mv source name is " + sourceName);
    log("mv source dir is " + sourcePath);
    log("mv dest name is " + destName);
    log("mv dest dir is " + destPath);

    int sourceDirBlock = getDirBlock(sourcePath);

    dir_entry sourceDirEntries[BLOCK_SIZE];
    this->disk.read(sourceDirBlock, (uint8_t *)sourceDirEntries);
    int fileBlock = -1;
    int metadatapos = -1;

    // loop through dir
    for (int i = 0; i < BLOCK_SIZE / sizeof(dir_entry); i++)
    {
        // check if file is not empty
        if (&sourceDirEntries[i].size != 0)
        {
            // check if file is a dir
            if (sourceDirEntries[i].type == TYPE_FILE)
            {
                // check if file name matches
                if (sourceDirEntries[i].file_name == sourceName)
                {
                    log("found file");
                    fileBlock = sourceDirEntries[i].first_blk;
                    metadatapos = i;
                    break;
                }
            }
        }
    }

    if (fileBlock == -1)
        return -1;

    // copy file to dest

    dir_entry file;
    file.size = sourceDirEntries[metadatapos].size;
    file.first_blk = sourceDirEntries[metadatapos].first_blk;
    file.type = sourceDirEntries[metadatapos].type;
    file.access_rights = sourceDirEntries[metadatapos].access_rights;

    strcpy(file.file_name, destName.c_str());

    dir_entry blank;
    blank.size = 0;
    blank.first_blk = 0;
    blank.type = 0;
    blank.access_rights = 0;
    strcpy(blank.file_name, "");

    sourceDirEntries[metadatapos] = blank;

    this->disk.write(sourceDirBlock, (uint8_t *)sourceDirEntries);
    // read dest dir
    dir_entry destDirEntries[BLOCK_SIZE];
    this->disk.read(destDirBlock, (uint8_t *)destDirEntries);

    int destPos = findSpotInFolder(destDirEntries);

    destDirEntries[destPos] = file;

    this->disk.write(destDirBlock, (uint8_t *)destDirEntries);

    return 0;
}

// rm <filepath> removes / deletes the file <filepath>
int FS::rm(std::string filepath)
{
    std::cout << "FS::rm(" << filepath << ")\n";

    std::string name;
    std::string path;

    auto parts = splitString(filepath, '/');

    name = parts[parts.size() - 1];
    parts.pop_back();

    path = joinVector(parts, "/");
    path = resolveFolderFromString(path, currentDir);

    // FIXME handle folders

    int folder = getDirBlock(path);

    dir_entry dir[BLOCK_SIZE];
    this->disk.read(folder, (uint8_t *)dir);
    int fileBlock = -1;
    // loop through dir
    for (int i = 0; i < BLOCK_SIZE / sizeof(dir_entry); i++)
    {
        // check if file is not empty
        if (&dir[i].size != 0)
        {
            // check if file is a dir
            // check if file name matches
            if (dir[i].file_name == name)
            {
                if (dir[i].type == TYPE_FILE)
                {
                    log("found file");
                    fileBlock = dir[i].first_blk;
                    // remove file from dir
                    dir[i].size = 0;
                    dir[i].first_blk = 0;
                    dir[i].type = 0;
                    dir[i].access_rights = 0;
                    strcpy(dir[i].file_name, "");
                    this->disk.write(folder, (uint8_t *)dir);
                    break;
                }
                else
                {
                    log("found folder");
                    bool shouldRemove = true;
                    fileBlock = dir[i].first_blk;
                    int dotIndex = -1;
                    dir_entry rmFolder[BLOCK_SIZE];
                    this->disk.read(dir[i].first_blk, (uint8_t *)rmFolder);
                    for (int j = 0; j < BLOCK_SIZE / sizeof(dir_entry); j++)
                    {
                        dir_entry entry = rmFolder[j];
                        if ((entry.type <= TYPE_FILE && entry.size <= 0) || (entry.type >= TYPE_DIR && entry.size == 0))
                        {
                            continue;
                        }
                        if (entry.size != 0)
                        {
                            // print current item

                            log("found item in folder");
                            log("item name is " + std::string(entry.file_name));

                            shouldRemove = false;
                            if (strcmp(entry.file_name, "..") == 0)
                            {
                                shouldRemove = true;
                                dotIndex = j;
                            }
                        }
                    }
                    if (!shouldRemove)
                    {
                        std::cout << "FS::rm - ERROR: Folder is not empty\n";
                        return -1;
                    }

                    rmFolder[dotIndex].size = 0;
                    rmFolder[dotIndex].first_blk = 0;
                    rmFolder[dotIndex].type = 0;
                    rmFolder[dotIndex].access_rights = 0;
                    strcpy(rmFolder[dotIndex].file_name, "");
                    this->disk.write(dir[i].first_blk, (uint8_t *)rmFolder);

                    // remove folder from dir
                    dir[i].size = 0;
                    dir[i].first_blk = 0;
                    dir[i].type = 0;
                    dir[i].access_rights = 0;
                    strcpy(dir[i].file_name, "");
                    this->disk.write(folder, (uint8_t *)dir);
                    break;
                }
            }
        }
    }
    log("file block is " + std::to_string(fileBlock));
    if (fileBlock == -1)
        return -1;

    // delete file from fat and from disk

    // zero disk blocks
    dir_entry blk[BLOCK_SIZE];
    std::memset(blk, 0, BLOCK_SIZE);

    while (fileBlock != FAT_EOF)
    {
        int nextBlock = this->fat[fileBlock];
        this->fat[fileBlock] = FAT_FREE;
        this->disk.write(fileBlock, (uint8_t *)blk);
        fileBlock = nextBlock;
    }

    return 0;
}

// append <filepath1> <filepath2> appends the contents of file <filepath1> to
// the end of file <filepath2>. The file <filepath1> is unchanged.
int FS::append(std::string filepath1, std::string filepath2)
{
    std::cout << "FS::append(" << filepath1 << "," << filepath2 << ")\n";

    std::string name1;
    std::string dir1;

    int pathOp = resolve(filepath1, false, name1, dir1);

    if (pathOp == -1)
    {
        std::cout << "FS::cat - ERROR: Path resolved failed\n";
        return -1;
    }

    std::string name2;
    std::string dir2;

    pathOp = resolve(filepath2, false, name2, dir2);

    std::string file1 = readFile(dir1, name1);
    std::string file2 = readFile(dir2, name2);

    if (pathOp == -1)
    {
        std::cout << "FS::cat - ERROR: Path resolved failed\n";
        return -1;
    }

    if (file1 == "ERR_FILENOTFOUND")
    {
        std::cout << "FS::append - ERROR: File not found\n";
        return -1;
    }
    if (file1 == "ERR_NOFILE")
    {
        std::cout << "FS::append - ERROR: File is not a file\n";
        return -1;
    }
    if (file1 == "ERR_NOACCESS")
    {
        std::cout << "FS::append - ERROR: No read access\n";
        return -1;
    }
    if (file2 == "ERR_FILENOTFOUND")
    {
        std::cout << "FS::append - ERROR: File not found\n";
        return -1;
    }
    if (file2 == "ERR_NOFILE")
    {
        std::cout << "FS::append - ERROR: File is not a file\n";
        return -1;
    }
    if (file2 == "ERR_NOACCESS")
    {
        std::cout << "FS::append - ERROR: No read access\n";
        return -1;
    }

    file2 += file1;

    rm(filepath2);
    writeFile(file2, getFileName(filepath2), resolveFolderFromString(filepath2, currentDir));

    return 0;
}

// mkdir <dirpath> creates a new sub-directory with the name <dirpath>
// in the current directory
int FS::mkdir(std::string dirpath)
{
    std::cout << "FS::mkdir(" << dirpath << ")\n";

    std::string name1;
    std::string dir1;

    int pathOp = resolve(dirpath, false, name1, dir1);

    if (pathOp == -1)
    {
        std::cout << "FS::cat - ERROR: Path resolved failed\n";
        return -1;
    }

    if (dirpath.length() > 56)
    {
        std::cout << "FS::mkdir - ERROR: Dir path is to long\n";
        return -1;
    }

    log("name is " + name1);
    log("dir is " + dir1);

    int dirBlock = getDirBlock(dir1);

    if (dirBlock == -1)
        return -1;

    dir_entry currentDirEntrys[BLOCK_SIZE];
    this->disk.read(dirBlock, (uint8_t *)currentDirEntrys);

    // check if dir already exists
    for (int i = 0; i < BLOCK_SIZE / sizeof(dir_entry); i++)
    {

        if (currentDirEntrys[i].file_name == dirpath)
        {
            std::cout << "FS::mkdir - ERROR: Name already exists\n";
            return -1;
        }
    }

    int freeDirEntryIndex = -1;

    for (int i = 0; i < BLOCK_SIZE / sizeof(dir_entry); i++)
    {
        dir_entry entry = currentDirEntrys[i];

        if ((entry.type <= TYPE_FILE && entry.size > 0) || (entry.type >= TYPE_DIR))
        {
            continue;
        }

        freeDirEntryIndex = i;
        break;
    }

    if (freeDirEntryIndex == -1)
    {
        std::cout << "FS::mkdir - ERROR: No free space in folder\n";
        return -1;
    }

    int newBlock = findFreeFatBlock();

    if (newBlock == -1)
    {
        std::cout << "FS::mkdir - ERROR: No free blocks\n";
        return -1;
    }

    log("new block is " + std::to_string(newBlock));

    // create folder
    dir_entry folder;
    folder.size = 1;
    folder.first_blk = newBlock;
    folder.type = TYPE_DIR;
    folder.access_rights = READ | WRITE | EXECUTE;
    strcpy(folder.file_name, name1.c_str());

    currentDirEntrys[freeDirEntryIndex] = folder;

    dir_entry newFolder[BLOCK_SIZE];
    this->disk.read(folder.first_blk, (uint8_t *)newFolder);

    // add .. entry

    dir_entry parent;
    parent.first_blk = dirBlock;
    parent.type = TYPE_DIR;
    parent.access_rights = READ | WRITE | EXECUTE;
    parent.size = 1;
    strcpy(parent.file_name, "..");

    newFolder[0] = parent;

    fat[newBlock] = FAT_EOF;

    this->disk.write(FAT_BLOCK, (uint8_t *)fat);
    this->disk.write(folder.first_blk, (uint8_t *)newFolder);
    log("writing new folder to disk block " + std::to_string(folder.first_blk));
    this->disk.write(dirBlock, (uint8_t *)currentDirEntrys);
    log("writing current dir to disk block " + std::to_string(dirBlock));

    return 0;
}

// cd <dirpath> changes the current (working) directory to the directory named <dirpath>
int FS::cd(std::string dirpath)
{
    std::cout << "FS::cd(" << dirpath << ")\n";

    if (dirpath == "/")
    {
        currentDir = "/";
        currDir = ROOT_BLOCK;
        return 0;
    }

    if (dirpath == "..")
    {
        if (currDir == ROOT_BLOCK)
        {
            currentDir = "/";
            return 0;
        }

        // read curr dir
        dir_entry dir[BLOCK_SIZE];
        this->disk.read(currDir, (uint8_t *)dir);

        currDir = dir[0].first_blk;
        currentDir = cutFileName(currentDir);
        if (currDir == ROOT_BLOCK)
        {
            currentDir = "/";
        }

        return 0;
    }
    // if it starts with / then it is an absolute path
    if (dirpath[0] == '/')
    {
        currDir = ROOT_BLOCK;
        currentDir = "/";
        dirpath.erase(0, 1);
    }
    dirpath = absolutePath(currentDir, dirpath);

    int pathBlock = getPathBlockId(dirpath);

    if (pathBlock == -1)
        return -1;

    currDir = pathBlock;
    currentDir = resolveFolderFromString(dirpath, currentDir);
    return 0;
}

// pwd prints the full path, i.e., from the root directory, to the current
// directory, including the currect directory name
int FS::pwd()
{

    printf("%s \n", currentDir.c_str());
    return 0;
}

// chmod <accessrights> <filepath> changes the access rights for the
// file <filepath> to <accessrights>.
int FS::chmod(std::string accessrights, std::string filepath)
{
    std::cout << "FS::chmod(" << filepath << ")\n";

    std::string absPathToFile = absolutePath(currentDir, filepath);

    std::string name = getFileName(filepath);

    absPathToFile = cutFileName(absPathToFile);

    int dirblock = getDirBlock(absPathToFile);

    dir_entry dirEntries[BLOCK_SIZE];
    this->disk.read(dirblock, (uint8_t *)dirEntries);
    int fileBlock = -1;

    // loop through dir
    for (int i = 0; i < BLOCK_SIZE / sizeof(dir_entry); i++)
    {
        // check if file is not empty
        if (&dirEntries[i].size != 0)
        {
            // log name
            log("name is " + std::string(dirEntries[i].file_name));
            // check if file name matches
            if (dirEntries[i].file_name == name)
            {
                log("found entry");
                fileBlock = i;
                break;
            }
        }
    }

    if (fileBlock == -1)
    {
        std::cout << "FS::chmod - ERROR: File not found\n";
        return -1;
    }

    dirEntries[fileBlock].access_rights = stoi(accessrights);
    log("access rights are " + std::to_string(dirEntries[fileBlock].access_rights));
    this->disk.write(dirblock, (uint8_t *)dirEntries);

    return 0;
}

int FS::getPathBlockId(int from, std::string path)
{
    if (path.empty())
    {
        return from;
    }
    if (path == ".")
    {
        return from;
    }

    if (path[0] == '/')
    {
        from = ROOT_BLOCK;
        path.erase(0, 1);
    }

    // split path into vector
    std::vector<std::string> pathVector;

    std::string delimiter = "/";
    size_t pos = 0;
    std::string token;
    while ((pos = path.find(delimiter)) != std::string::npos)
    {
        token = path.substr(0, pos);
        pathVector.push_back(token);
        path.erase(0, pos + delimiter.length());
    }

    // loop through path
    for (std::string dir : pathVector)
    {
        // read current dir
        dir_entry folder[BLOCK_SIZE];
        this->disk.read(from, (uint8_t *)folder);

        // loop through dir
        // FIXME: handle non existing dir
        for (int i = 0; i < BLOCK_SIZE / sizeof(dir_entry); i++)
        {
            // check if file is not empty
            if (&folder[i].size != 0)
            {
                // check if file is a dir
                if (folder[i].type == TYPE_DIR)
                {
                    // check if file name matches
                    if (folder[i].file_name == dir)
                    {
                        // set current dir to file block
                        from = folder[i].first_blk;
                        break;
                    }
                }
            }
        }
    }
    return from;
}

int FS::writeFile(std::string data, std::string name, std::string filePath)
{
    // write to disk
    log("writing to disk");
    log("path is " + filePath);
    int dirBlock = getDirBlock(filePath);
    std::string childName = getFileName(filePath);
    std::string parentFolder = cutFileName(filePath);
    int parentFolderBlock = getDirBlock(parentFolder);

    log("parent folder is " + parentFolder);
    // read parent folder block
    dir_entry parentFolderEntries[BLOCK_SIZE];
    this->disk.read(parentFolderBlock, (uint8_t *)parentFolderEntries);

    // loop over to find child folder
    int childFolderBlock = -1;
    for (int i = 0; i < BLOCK_SIZE / sizeof(dir_entry); i++)
    {
        if (parentFolderEntries[i].type == TYPE_DIR)
        {
            if (parentFolderEntries[i].file_name == childName)
            {
                childFolderBlock = i;
                break;
            }
        }
    }

    if (childFolderBlock != -1)
    {
        if (parentFolderEntries[childFolderBlock].access_rights & WRITE)
        {
            log("perms ok");
        }
        else
        {
            std::cout << "FS::writeFile - ERROR: No write access\n";
            return -1;
        }
    }

    this->log("dir block is " + std::to_string(dirBlock));

    int16_t block;
    int16_t prev;
    int16_t first;
    const char *charData = data.c_str();
    int dataLength = data.length();
    while (dataLength > 0)
    {
        // will be the same for the first block
        block = findFreeFatBlock();
        if (block == -1)
        {
            std::cout << "FS::create - ERROR: No free blocks\n";
            return -1;
        }

        // write data to block
        this->disk.write(block, (uint8_t *)charData);

        // update fat
        this->fat[block] = FAT_EOF;
        // check fat
        if (dataLength != data.length())
        {
            // runs after first time
            fat[prev] = block;
        }
        else
        {
            // runs first time
            first = block;
        }
        prev = block;

        dataLength -= BLOCK_SIZE;
        charData += BLOCK_SIZE;

        this->disk.write(FAT_BLOCK, (uint8_t *)fat);

        // define dir entry
        dir_entry file;
        file.size = data.length();
        file.first_blk = first;
        file.type = TYPE_FILE;
        file.access_rights = READ | WRITE | EXECUTE;
        strcpy(file.file_name, name.c_str());
        if (file.size == 0)
        {
            file.size = 1;
        }

        // 145-154

        dir_entry dir[BLOCK_SIZE];
        this->disk.read(dirBlock, (uint8_t *)dir);

        int entryId = findSpotInFolder(dir);

        if (entryId == -1)
        {
            std::cout << "FS::create - ERROR: No free space in folder\n";
            return -1;
        }

        dir[entryId] = file;

        this->disk.write(dirBlock, (uint8_t *)dir);
    }
    return 0;
}

std::string FS::getFileName(std::string path)
{
    std::string delimiter = "/";
    size_t pos = 0;
    std::string token;
    while ((pos = path.find(delimiter)) != std::string::npos)
    {
        token = path.substr(0, pos);
        path.erase(0, pos + delimiter.length());
    }
    return path;
}
std::string FS::resolveFolderFromString(std::string path, std::string currentDir)
{
    // If path is empty, return current directory
    if (path.empty())
    {
        return currentDir;
    }

    // Check if path is absolute. If so, reset current directory
    if (path[0] == '/')
    {
        currentDir = "/";
        path = path.substr(1);
    }

    // Split path into vector
    std::vector<std::string> pathVector;
    std::string delimiter = "/";
    size_t pos = 0;
    while ((pos = path.find(delimiter)) != std::string::npos)
    {
        pathVector.push_back(path.substr(0, pos));
        path = path.substr(pos + 1);
    }
    pathVector.push_back(path);

    // Process each directory in path
    for (const std::string &dir : pathVector)
    {
        if (dir == ".")
        {
            continue;
        }
        else if (dir == "..")
        {
            if (currentDir != "/")
            {
                size_t lastSlash = currentDir.find_last_of('/');
                currentDir = currentDir.substr(0, lastSlash);
            }
        }
        else
        {
            if (currentDir != "/")
            {
                currentDir += "/";
            }
            currentDir += dir;
        }
    }

    if (currentDir == "")
    {
        currentDir = "/";
    }

    return currentDir;
}

// Function to convert an absolute path to a block id
int FS::getPathBlockId(std::string path)
{
    int workingDir = currDir;
    // check if path is empty
    if (path.empty())
    {
        return workingDir;
    }

    // check if path is absolute
    if (path[0] == '/')
    {
        if (path == "/")
            return ROOT_BLOCK;
        workingDir = ROOT_BLOCK;
        path.erase(0, 1);
    }

    // split path into vector
    std::vector<std::string> pathVector;

    std::string delimiter = "/";
    size_t pos = 0;
    std::string token;
    while ((pos = path.find(delimiter)) != std::string::npos)
    {
        token = path.substr(0, pos);
        pathVector.push_back(token);
        path.erase(0, pos + delimiter.length());
    }

    pathVector.push_back(path);

    bool found = false;
    // loop through path
    for (std::string s : pathVector)
    {
        // read current dir
        dir_entry dir[BLOCK_SIZE];
        this->disk.read(workingDir, (uint8_t *)dir);

        // loop through dir
        for (int i = 0; i < BLOCK_SIZE / sizeof(dir_entry); i++)
        {
            // check if file is not empty
            if (&dir[i].size != 0)
            {
                // check if file is a dir
                if (dir[i].type == TYPE_DIR)
                {
                    // check if file name matches
                    if (dir[i].file_name == s)
                    {
                        // set current dir to file block
                        workingDir = dir[i].first_blk;
                        found = true;
                        break;
                    }
                }
            }
        }
    }
    if (!found)
    {
        return -1;
    }
    return workingDir;
}