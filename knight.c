#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

int stat(const char *pathname, struct stat *statbuf);
//char printMode (int mode);

int main(int argc, char *argv[])
{
	DIR *dir;
    struct dirent *direct;
    dir = opendir("./");

    while((direct = readdir(dir)) != 0)
    {
    	struct stat FileStat;
    	stat(direct->d_name, &FileStat);

    	chmod(direct->d_name, FileStat.st_mode);

    	struct passwd *usn;
    	usn = getpwuid(FileStat.st_uid);
    	struct group *grn;
    	grn = getgrgid(FileStat.st_gid);

    	struct tm ti;
    	localtime_r(&FileStat.st_mtime, &ti);
    	char StatTime[13];
    	strftime (StatTime, sizeof(StatTime), "%b %d %H:%M", &ti);

    	printf( (S_ISDIR(FileStat.st_mode)) ? "d" : "-");
    	printf( (FileStat.st_mode & S_IRUSR) ? "r" : "-");
    	printf( (FileStat.st_mode & S_IWUSR) ? "w" : "-");
    	printf( (FileStat.st_mode & S_IXUSR) ? "x" : "-");
    	printf( (FileStat.st_mode & S_IRGRP) ? "r" : "-");
    	printf( (FileStat.st_mode & S_IWGRP) ? "w" : "-");
    	printf( (FileStat.st_mode & S_IXGRP) ? "x" : "-");
    	printf( (FileStat.st_mode & S_IROTH) ? "r" : "-");
    	printf( (FileStat.st_mode & S_IWOTH) ? "w" : "-");
    	printf( (FileStat.st_mode & S_IXOTH) ? "x" : "-");   

    	printf("%ld %s %s %ld %s %s\n", FileStat.st_nlink, usn->pw_name, grn->gr_name, FileStat.st_size, StatTime, direct->d_name);
    }
    closedir(dir);

	return 0;
}

/*char printMode (int mode)
{
	short i = 0;
	char str[10];
	switch((mode>>9)<<9)
	{
		case S_IFBLK:
			str[0] = 'b';
			break;
		case S_IFCHR:
			str[0] = 'c';
			break;
		case S_IFDIR:
			str[0] = 'd';
			break;
		case S_IFIFO:
			str[0] = 'p';
			break;
		case S_IFREG:
			str[0] = '-';
			break;
		case S_IFLNK:
			str[0] = 'l';
			break;
	}

	 str[++i] = ((mode & S_IRUSR) ? 'r' : '-');
     str[++i] = ((mode & S_IWUSR) ? 'w' : '-');
     str[++i] = ((mode & S_IXUSR) ? 'x' : '-');
     str[++i] = ((mode & S_IRGRP) ? 'r' : '-');
     str[++i] = ((mode & S_IWGRP) ? 'w' : '-');
     str[++i] = ((mode & S_IXGRP) ? 'x' : '-');
     str[++i] = ((mode & S_IROTH) ? 'r' : '-');
     str[++i] = ((mode & S_IWOTH) ? 'w' : '-');
     str[++i] = ((mode & S_IXOTH) ? 'x' : '-');
     return str;
}

*/