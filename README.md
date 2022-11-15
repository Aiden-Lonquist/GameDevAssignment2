# GameDevAssignment2

Part 1:
<br /><br />

Part 2:
&nbsp;Line was added to define pDst[3] so that the destination alpha could be accessed. (Line 41)<br />
&nbsp;MMX Mode:<br />
&nbsp;&nbsp;changed pSrc[3] pointer lines to use pDst[3] instead. (Lines 51, 52)<br />
<br />
&nbsp;Serial Mode:<br /> 
&nbsp;&nbsp;changed pSrc[3] to pDst[3] (Lines 188, 192, 196)<br />
<br />
&nbsp;Intrinsic Mode:<br />
&nbsp;&nbsp;changed pSrc[3] to pDst[3] (Line 216)<br />
<br />
<br />
Part 3:<br />
&nbsp;Created an empty function "funcValue" that takes in a parameter as a value.<br />
&nbsp;when calling the function, the assembly looks like this:<br />
&nbsp;&nbsp;funcValue(optarg);<br />
&nbsp;&nbsp;mov   eax, dword ptr [optarg]<br />
&nbsp;&nbsp;push  eax<br />
&nbsp;&nbsp;call  funcValue (03BCCA3h)<br />
&nbsp;&nbsp;add   esp, 4<br />
<br />
&nbsp;Created another empty function "funcReference" that takes in a parameter as a reference<br />
&nbsp;When calling the function, the assembly looks like this:<br />
&nbsp;&nbsp;funcReference(optarg);<br />
&nbsp;&nbsp;lea   eax, [optarg]<br />
&nbsp;&nbsp;push  eax<br />
&nbsp;&nbsp;call  funcReference (03BC7EEh)<br />
&nbsp;&nbsp;add   esp, 4<br />
<br />
&nbsp;The difference between the reference and value function is on the first line.<br />
&nbsp;In the value function, a pointer is used pointer to the parameter.<br />
&nbsp;In the reference function the address of the memory for the parameter is used instead.<br />
<br />
<br />
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
