# GameDevAssignment2

<b>Part 1:</b><br />
TODO<br />
Describe MMX mode (assembly)<br />
<br />
TODO<br />
Describe Regular C++ mode<br />
&nbsp;&nbsp;(rough copy below)<br />
&nbsp;&nbsp;This mode is written in regular c++<br />
&nbsp;&nbsp;It works by calculating the difference between the Src and Dst<br />
&nbsp;&nbsp;It then multiplies the destination by the difference between source and destination<br />
&nbsp;&nbsp;Lastly, it says that the destination is the temp answer from the previous line plus the original destination<br />
&nbsp;&nbsp;It does this for each color (R, G, B) and each pixel.<br />
&nbsp;&nbsp;Then in increments all of the colors and alphas for source and destination by one. <br />
<br />
TODO<br />
Describe Intrinsic mode<br />
<br />
Speed of Modes:<br />
&nbsp;&nbsp;The fastest mode is MMX which is written in assembly<br />
&nbsp;&nbsp;The second fastest mode is Intrinsic which uses registers<br />
&nbsp;&nbsp;The slowest mode is the regular c++<br />

<br /><br />

<b>Part 2:</b><br />
&nbsp;&nbsp;Line was added to define pDst[3] so that the destination alpha could be accessed. (Line 41)<br />
&nbsp;&nbsp;MMX Mode:<br />
&nbsp;&nbsp;&nbsp;&nbsp;changed pSrc[3] pointer lines to use pDst[3] instead. (Lines 51, 52)<br />
<br />
&nbsp;&nbsp;Serial Mode:<br /> 
&nbsp;&nbsp;&nbsp;&nbsp;changed pSrc[3] to pDst[3] (Lines 188, 192, 196)<br />
<br />
&nbsp;&nbsp;Intrinsic Mode:<br />
&nbsp;&nbsp;&nbsp;&nbsp;changed pSrc[3] to pDst[3] (Line 216)<br />
<br />
<br />
<b>Part 3:</b><br />
&nbsp;&nbsp;Created an empty function "funcValue" that takes in a parameter as a value.<br />
&nbsp;&nbsp;when calling the function, the assembly looks like this:<br />
&nbsp;&nbsp;&nbsp;&nbsp;funcValue(optarg);<br />
&nbsp;&nbsp;&nbsp;&nbsp;mov &nbsp;&nbsp;&nbsp;eax, dword ptr [optarg]<br />
&nbsp;&nbsp;&nbsp;&nbsp;push&nbsp;&nbsp;&nbsp;eax<br />
&nbsp;&nbsp;&nbsp;&nbsp;call&nbsp;&nbsp;&nbsp;funcValue (03BCCA3h)<br />
&nbsp;&nbsp;&nbsp;&nbsp;add &nbsp;&nbsp;&nbsp;esp, 4<br />
<br />
&nbsp;&nbsp;Created another empty function "funcReference" that takes in a parameter as a reference<br />
&nbsp;&nbsp;When calling the function, the assembly looks like this:<br />
&nbsp;&nbsp;&nbsp;&nbsp;funcReference(optarg);<br />
&nbsp;&nbsp;&nbsp;&nbsp;lea &nbsp;&nbsp;&nbsp;eax, [optarg]<br />
&nbsp;&nbsp;&nbsp;&nbsp;push&nbsp;&nbsp;&nbsp;eax<br />
&nbsp;&nbsp;&nbsp;&nbsp;call&nbsp;&nbsp;&nbsp;funcReference (03BC7EEh)<br />
&nbsp;&nbsp;&nbsp;&nbsp;add &nbsp;&nbsp;&nbsp;esp, 4<br />
<br />
&nbsp;&nbsp;The difference between the reference and value function is on the first line.<br />
&nbsp;&nbsp;In the value function, a pointer is used pointer to the parameter.<br />
&nbsp;&nbsp;In the reference function the address of the memory for the parameter is used instead.<br />
<br />
<br />
<b>Part 4:</b><br />
&nbsp;&nbsp;Created a function "funcMath" that does a simple math calculation.<br />
&nbsp;&nbsp;When calling the function, the assembly looks like this:<br />
&nbsp;&nbsp;&nbsp;&nbsp;funcMath();<br />
&nbsp;&nbsp;&nbsp;&nbsp;call&nbsp;&nbsp;&nbsp;funcMath<br />
<br />
&nbsp;&nbsp;Created an inline function "funcMathInline" that does a simple math calculation.<br />
&nbsp;&nbsp;When calling the function, the assembly looks like this:<br />
&nbsp;&nbsp;funcMathInline();<br />
&nbsp;&nbsp;&nbsp;&nbsp;call&nbsp;&nbsp;&nbsp;funcMathInline<br />
<br />
&nbsp;&nbsp;I didn't notice a difference between the inline function and the regular function<br />
&nbsp;&nbsp;in assembly.<br />
