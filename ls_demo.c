#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <stdio.h>
 
#define FALSE 0
#define TRUE !FALSE
 
extern  int alphasort();
 
char pathname[MAXPATHLEN];
 
main()   
{ 
    int count,i;
		struct direct **files;
		int file_select();
 
		if (getwd(pathname) == NULL )
		{ 
      printf("Error getting pathn");
			exit(0);
		}
				
    printf("Current Working Directory = %sn",pathname);
		count =  scandir(pathname, &files, file_select, alphasort);
 
		/* If no files found, make a non-selectable menu item */
		if (count <= 0)
		{		 
      printf("No files in this directoryn");
			exit(0);
		}
		printf("Number of files = %dn",count);
		for (i=1;i<count+1;++i)
		  printf("%s  ",files[i-1]->d_name);
		printf("n"); /* flush buffer */
}



int file_select(struct direct   *entry)
{
    if ((strcmp(entry->d_name, ".") == 0) ||
		  (strcmp(entry->d_name, "..") == 0))
		  return (FALSE);
		else
		  return (TRUE);
}


int file_select_1(struct direct   *entry)
{
    char *ptr;
		char *rindex(char *s, char c);
 
		if ((strcmp(entry->d_name, ".")== 0) ||
			(strcmp(entry->d_name, "..") == 0))
			return (FALSE);
 
		/* Check for filename extensions */
		ptr = rindex(entry->d_name, '.')
		if ((ptr != NULL) &&
		  ((strcmp(ptr, ".c") == 0)
			(strcmp(ptr, ".h") == 0)
			(strcmp(ptr, ".o") == 0) ))
			 return (TRUE);
	 else
		 return(FALSE);
}