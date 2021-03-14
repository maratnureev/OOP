SET programPath="%~1"

%programPath% input.txt output.txt || goto err
fc output.txt expected.txt || goto err 

%programPath% input1.txt output.txt || goto err
fc output.txt expected1.txt || goto err 

%programPath% input2.txt output.txt || goto err
fc output.txt expected2.txt || goto err 

%programPath% input3.txt output.txt > output.txt
if not errorlevel 1 goto err

echo Tests passed
exit /B 0

:err
echo Test failed
exit /B 1