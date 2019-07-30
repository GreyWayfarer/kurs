int read(char *pth)
{
    char path[1000];
    strcpy(path, pth);
    DIR *dp;
    struct dirent *files;
    if((dp=opendir(path))!= NULL)
        perror("dir\n");
    char newp[1000];
    while((files=readdir(dp)!= NULL)
    {
        if(!strcmp(files->d_name, ".") || !strcmp(files->d_name, ".."))
            continue;
    strcpy(newp, path);
    strcat()
