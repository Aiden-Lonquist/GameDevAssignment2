# GameDevAssignment2

Part 1:


Part 2:
  &nbsp;Line was added to define pDst[3] so that the destination alpha could be accessed. (Line 41)
  &nbsp;MMX Mode:
    &nbsp;&nbsp;changed pSrc[3] pointer lines to use pDst[3] instead. (Lines 51, 52)

  &nbsp;Serial Mode:  
    &nbsp;&nbsp;changed pSrc[3] to pDst[3] (Lines 188, 192, 196)

  &nbsp;Intrinsic Mode:
    &nbsp;&nbsp;changed pSrc[3] to pDst[3] (Line 216)


Part 3:
  Created an empty function "funcValue" that takes in a parameter as a value.
  when calling the function, the assembly looks like this:
    funcValue(optarg);
    mov   eax, dword ptr [optarg]
    push  eax
    call  funcValue (03BCCA3h)
    add   esp, 4
    
  Created another empty function "funcReference" that takes in a parameter as a reference
  When calling the function, the assembly looks like this:
    funcReference(optarg);
    lea   eax, [optarg]
    push  eax
    call  funcReference (03BC7EEh)
    add   esp, 4
    
  The difference between the reference and value function is on the first line. 
  In the value function, a pointer is used pointer to the parameter.
  In the reference function the address of the memory for the parameter is used instead.


Part 4:
  Created a function "funcMath" that does a simple math calculation.
  When calling the function, the assembly looks like this:
    funcMath();
    call funcMath
  
  Created an inline function "funcMathInline" that does a simple math calculation.
  When calling the function, the assembly looks like this:
    funcMathInline();
    call funcMathInline
    
  I didn't notice a difference between the inline function and the regular function
  in assembly.
