# GameDevAssignment2

<h2>Part 1:</h2><br />
Note: Aside from the comments in this file, the code is also commented.<br />
<br />
<b>Describe MMX mode:</b><br />
&nbsp;&nbsp;The first block of this mode defines a pointer to the alpha blend factor that will be used<br />
&nbsp;&nbsp;It originally was pointing to pSrc[3] but was changed to pDst[3] for part 2.<br />
&nbsp;&nbsp;The next block handles the blending of the red<br />
&nbsp;&nbsp;It starts by creating a pointer to the destination[0] which is red.<br />
&nbsp;&nbsp;Next, it interleaves the low half and after that the high half much like the intrinsic mode<br />
&nbsp;&nbsp;Then, it gets the pointer for the source red.<br />
&nbsp;&nbsp;Again, it does the functions for low bits first and then high bits<br />
&nbsp;&nbsp;The results are bit shifted by 8 and then replace the destination<br />
&nbsp;&nbsp;The same process repeats for green and then blue.<br />
&nbsp;&nbsp;The difference for green is that pSrc and pDst are now called with + 4 to point to green<br />
&nbsp;&nbsp;For blue it's the same but + 8 instead of + 4.<br />
<br />
<b>Describe Regular C++ mode:</b><br />
&nbsp;&nbsp;This mode is written in regular c++<br />
&nbsp;&nbsp;It works by calculating the difference between the Src and Dst<br />
&nbsp;&nbsp;It then multiplies the destination by the difference between source and destination<br />
&nbsp;&nbsp;It also bit shifts the result by 8 on this line<br />
&nbsp;&nbsp;Lastly, it says that the destination is the temp answer from the previous line plus the original destination<br />
&nbsp;&nbsp;It does this for each color (R, G, B) and each pixel.<br />
&nbsp;&nbsp;Then in increments all of the colors and alphas for source and destination by one. <br />
<br />
<b>Describe Intrinsic mode:</b><br />
&nbsp;&nbsp;This mode is written in c++ but makes use of registers.<br />
&nbsp;&nbsp;It starts by assigning several variables to registers instead of storing them in regular memory.<br />
&nbsp;&nbsp;It then runs the setzero function with means all elements will start at 0<br />
&nbsp;&nbsp;Next, it unpacks and interleaves 8-bit integers from low half<br />
&nbsp;&nbsp;After, it unpacks and interleaves 8-bit integers from high half<br />
&nbsp;&nbsp;Then, it calls the blend function for each color (R, G, B)<br />
<br />
<b>Speed of Modes:</b><br />
&nbsp;&nbsp;The fastest mode is MMX which is written in assembly<br />
&nbsp;&nbsp;The second fastest mode is Intrinsic which uses registers<br />
&nbsp;&nbsp;The slowest mode is the regular c++<br />

<br /><br />

<h2>Part 2:</h2><br />
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
<h2>Part 3:</h2><br />
&nbsp;&nbsp;Created an empty function <b>"funcValue"</b> that takes in a parameter as a value.<br />
&nbsp;&nbsp;when calling the function, the assembly looks like this:<br />
&nbsp;&nbsp;&nbsp;&nbsp;funcValue(optarg);<br />
&nbsp;&nbsp;&nbsp;&nbsp;mov &nbsp;&nbsp;&nbsp;eax, dword ptr [optarg]<br />
&nbsp;&nbsp;&nbsp;&nbsp;push&nbsp;&nbsp;&nbsp;eax<br />
&nbsp;&nbsp;&nbsp;&nbsp;call&nbsp;&nbsp;&nbsp;funcValue (03BCCA3h)<br />
&nbsp;&nbsp;&nbsp;&nbsp;add &nbsp;&nbsp;&nbsp;esp, 4<br />
<br />
&nbsp;&nbsp;Created another empty function <b>"funcReference"</b> that takes in a parameter as a reference<br />
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
<h2>Part 4:</h2><br />
&nbsp;&nbsp;Created a function <b>"funcMath"</b> that does a simple math calculation.<br />
&nbsp;&nbsp;When calling the function, the assembly looks like this:<br />
&nbsp;&nbsp;&nbsp;&nbsp;funcMath();<br />
&nbsp;&nbsp;&nbsp;&nbsp;call&nbsp;&nbsp;&nbsp;funcMath<br />
<br />
&nbsp;&nbsp;Created an inline function <b>"funcMathInline"</b> that does a simple math calculation.<br />
&nbsp;&nbsp;When calling the function, the assembly looks like this:<br />
&nbsp;&nbsp;funcMathInline();<br />
&nbsp;&nbsp;&nbsp;&nbsp;call&nbsp;&nbsp;&nbsp;funcMathInline<br />
<br />
&nbsp;&nbsp;I didn't notice a difference between the inline function and the regular function<br />
&nbsp;&nbsp;in assembly.<br />
