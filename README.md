# GameDevAssignment2

Part 1:
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
Part 3:<br />
&nbsp;&nbsp;Created an empty function "funcValue" that takes in a parameter as a value.<br />
&nbsp;&nbsp;when calling the function, the assembly looks like this:<br />
&nbsp;&nbsp;&nbsp;&nbsp;funcValue(optarg);<br />
&nbsp;&nbsp;&nbsp;&nbsp;mov   eax, dword ptr [optarg]<br />
&nbsp;&nbsp;&nbsp;&nbsp;push  eax<br />
&nbsp;&nbsp;&nbsp;&nbsp;call  funcValue (03BCCA3h)<br />
&nbsp;&nbsp;&nbsp;&nbsp;add   esp, 4<br />
<br />
&nbsp;&nbsp;Created another empty function "funcReference" that takes in a parameter as a reference<br />
&nbsp;&nbsp;When calling the function, the assembly looks like this:<br />
&nbsp;&nbsp;&nbsp;&nbsp;funcReference(optarg);<br />
&nbsp;&nbsp;&nbsp;&nbsp;lea   eax, [optarg]<br />
&nbsp;&nbsp;&nbsp;&nbsp;push  eax<br />
&nbsp;&nbsp;&nbsp;&nbsp;call  funcReference (03BC7EEh)<br />
&nbsp;&nbsp;&nbsp;&nbsp;add   esp, 4<br />
<br />
&nbsp;&nbsp;The difference between the reference and value function is on the first line.<br />
&nbsp;&nbsp;In the value function, a pointer is used pointer to the parameter.<br />
&nbsp;&nbsp;In the reference function the address of the memory for the parameter is used instead.<br />
<br />
<br />
Part 4:<br />
&nbsp;&nbsp;Created a function "funcMath" that does a simple math calculation.<br />
&nbsp;&nbsp;When calling the function, the assembly looks like this:<br />
&nbsp;&nbsp;&nbsp;&nbsp;funcMath();<br />
&nbsp;&nbsp;&nbsp;&nbsp;call funcMath<br />
<br />
&nbsp;&nbsp;Created an inline function "funcMathInline" that does a simple math calculation.<br />
&nbsp;&nbsp;When calling the function, the assembly looks like this:<br />
&nbsp;&nbsp;funcMathInline();<br />
&nbsp;&nbsp;&nbsp;&nbsp;call funcMathInline<br />
<br />
&nbsp;&nbsp;I didn't notice a difference between the inline function and the regular function<br />
&nbsp;&nbsp;in assembly.<br />
