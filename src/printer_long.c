#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include "../include/ft_ls.h"

static char get_file_type(mode_t mode)
{
    if (S_ISDIR(mode))
        return ('d');
    if (S_ISLNK(mode))
        return ('l');
    if (S_ISCHR(mode))
        return ('c');
    if (S_ISBLK(mode))
        return ('b');
    if (S_ISFIFO(mode))
        return ('p');
    if (S_ISSOCK(mode))
        return ('s');
    return ('-');
}

static void print_permissions(mode_t mode)
{
    ft_printf("%c", (mode & S_IRUSR) ? 'r' : '-');
    ft_printf("%c", (mode & S_IWUSR) ? 'w' : '-');
    ft_printf("%c", (mode & S_IXUSR) ? 'x' : '-');
    ft_printf("%c", (mode & S_IRGRP) ? 'r' : '-');
    ft_printf("%c", (mode & S_IWGRP) ? 'w' : '-');
    ft_printf("%c", (mode & S_IXGRP) ? 'x' : '-');
    ft_printf("%c", (mode & S_IROTH) ? 'r' : '-');
    ft_printf("%c", (mode & S_IWOTH) ? 'w' : '-');
    ft_printf("%c", (mode & S_IXOTH) ? 'x' : '-');
}

static void print_date(time_t mtime)
{
    char    *date;
    int     i;

    date = ctime(&mtime);
    if (!date)
        return ;
    i = 4;
    while (i < 16)
    {
        write(1, &date[i], 1);
        i++;
    }
}

static void print_link_target(t_file *file)
{
    char    buf[1024];
    ssize_t len;

    len = readlink(file->path, buf, sizeof(buf) - 1);
    if (len == -1)
        return ;
    buf[len] = '\0';
    ft_printf(" -> %s", buf);
}

void    print_ls_long(void *content)
{
    t_file          *file;
    struct passwd   *pwd;
    struct group    *grp;

    file = (t_file *)content;
    if (!file)
        return ;
    pwd = getpwuid(file->st.st_uid);
    grp = getgrgid(file->st.st_gid);
    ft_printf("%c", get_file_type(file->st.st_mode));
    print_permissions(file->st.st_mode);
    ft_printf(" %ld", (long)file->st.st_nlink);
    ft_printf(" %s", pwd ? pwd->pw_name : "unknown");
    ft_printf(" %s", grp ? grp->gr_name : "unknown");
    ft_printf(" %lld ", (long long)file->st.st_size);
    print_date(file->st.st_mtime);
    ft_printf(" %s", file->name);
    if (S_ISLNK(file->st.st_mode))
        print_link_target(file);
    ft_printf("\n");
}