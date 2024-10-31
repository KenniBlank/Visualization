# Visualization
SDL2 Based Visualization of core concepts of programming and mathematics or anything that I want to see.

- Usecase:  
compile with Make file.  
Use case: "make SOURCE=nameOfFile.c"  

- If you Dont want to install SDL2
    ```bash
    make SOURCE=cli.h #use at the top directory
    ```


# Files:
- **common.h**  
    This header contains all the common headers, functions, declarations, constants, etc that are common in all functions.  
    It has the necessary setup, destroy, frameLimit function that are needed in all programs.


- **sineCosForRotation.c**  
    This file shows a square being rotated which is done with sine and cos.   
    - Press 'p' key to pause/Play. 
    - Close application with 'Escape' or close button.  
    - You can Also change the speed of the rotation by using up and down arrows.  
    ```bash
    # Compile with:
    make SOURCE=./MathematicalPatterns/sineCosForRotation.c
    ```

- **complexNumberForRotation.c**
    Lets See... Or Lets C...
