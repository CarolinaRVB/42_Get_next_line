# 42_Get_next_line

## Description
The "Get Next Line" function is a utility in C programming that reads a file line by line. It's particularly useful when you need to process a file line by line without loading the entire file into memory.

## How to Use
To use the "Get Next Line" function in your C project, follow these steps:

1. **Include the Header File:** Include the header file `get_next_line.h` in your source code file where you want to use the function.

    ```c
    #include "get_next_line.h"
    ```

2. **Call the Function:** Call the `get_next_line` function with the file descriptor of the file you want to read from.

    ```c
    char *line;
    int fd;

    // Open the file
    fd = open("filename.txt", O_RDONLY);

    // Read lines from the file until EOF
    while (get_next_line(fd, &line) > 0)
    {
        // Process the line
        printf("%s\n", line);

        // Free the memory allocated by get_next_line
        free(line);
    }

    // Close the file descriptor
    close(fd);
    ```

3. **Compile:** Compile your code with the `get_next_line.c` file.

    ```bash
    gcc -o your_program your_program.c get_next_line.c
    ```

4. **Run:** Execute your compiled program.

    ```bash
    ./your_program
    ```

## Parameters
- **fd:** The file descriptor of the file you want to read from.
- **line:** A pointer to a character pointer (`char **`) where the line read from the file will be stored.

## Return Value
- If a line is read successfully, the function returns `1`.
- If the end of the file is reached, the function returns `0`.
- If an error occurs, the function returns `-1`.

## Dependencies
- This function depends on the `unistd.h` and `stdlib.h` headers.
- It also requires the `open`, `read`, and `close` system calls.

## Notes
- Make sure to handle memory allocation for the `line` pointer properly. You must free the memory allocated for each line after you're done processing it.
- This function is designed to handle reading from a file descriptor, which means it can be used for reading from standard input (`stdin`), files, sockets, or any other file descriptor source.


## License
This project is licensed under the [MIT License](LICENSE).