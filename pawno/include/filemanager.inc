native file_move(file[], destination[]);
native file_copy(file[], destination[]);
native file_delete(file[]);
native file_create(file[]);
native file_write(file[], text[], mode[] = "a");
native file_read(file[], storage[], size = sizeof(storage));
native file_log();
native file_exists(file[]);
native File:f_open(file[], mode[] = "r"); 
native f_close(File: file);
native f_read(File: file, storage[], size = sizeof(storage));
native f_write(File: file, string[]);

/*
	Function: dir_create(directory[]);
	Description: Creates a directory.
	Params:
			directory[] - The path of the directory to be created.
			
	Returns: True if success, false if not.
*/
native dir_create(directory[]);

/*
	Function: dir_delete(directory[]);
	Description: Deletes a directory.
	Params:
			directory[] - The path of the directory to be deleted.
			
	Returns: True if success, false if not.
*/
native dir_delete(directory[]);

/*
	Function: dir_exists(directory[]);
	Description: Checks if a directory exists
	Params:
			directory[] - The path of the directory to be deleted.
			
	Returns: 1 if it exists, 2 if it is a file and 0 if it does not exist.
*/
native dir_exists(directory[]);

/*
	Function: dir:dir_open(directory[]);
	Description: Opens a directory
	Params:
			directory[] - The path of the directory to be opened.
			
	Returns: 1 if it exists, and 0 if it does not exist.
*/
native dir:dir_open(directory[]);

/*
	Function: dir_close(dir:handle);
	Description: Closes a directory
	Params:
			dir:handle - The handle of the directory to close that was previously opened.
			
	Returns: Nothing.
*/
native dir_close(dir:handle);

/*
	Function: dir_list(dir:handle, storage[], &type, length = sizeof(storage));
	Description: Reads through a directory, listing each file/sub-directory one by one.
	Params:
			dir:handle - The handle of the directory that is open to read from.
			storage[] - Where the name of the file/directory is stored.
			type - Where the type of directory is stored, can be either 1 or 2
			(optional) length - This is not needed unless you are passing an array without any length, in which case, use strlen with your array.
			
	Returns: 1 if there a sub-directory/file was found, 0 if there wasn't.
*/
native dir_list(dir:handle, storage[], &type, length = sizeof(storage));

// FM_DIR defines a directory and FM_FILE defines a file
// when using dir_list, these will be the types returned.
#define FM_DIR 1
#define FM_FILE 2