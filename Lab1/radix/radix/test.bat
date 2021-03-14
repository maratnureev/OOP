SET programPath="%~1"

%programPath% 10 2 -10 > output.txt || goto err
fc output.txt expected1.txt || goto err 

%programPath% 36 2 ZZZ > output.txt || goto err
fc output.txt expected2.txt || goto err 

%programPath% 10 35 541252 > output.txt || goto err
fc output.txt expected3.txt || goto err 

%programPath% 16 35 -FF14F > output.txt || goto err
fc output.txt expected4.txt || goto err 

%programPath% 10 2 2147483647 > output.txt || goto err
fc output.txt expected5.txt || goto err 

%programPath% 10 2 -2147483648 > output.txt || goto err
fc output.txt expected6.txt || goto err 

%programPath% 10 1 10432 > output.txt
if not errorlevel 1 goto err

%programPath% 37 2 10432 > output.txt
if not errorlevel 1 goto err

%programPath% 10 2 2147483648 > output.txt
if not errorlevel 1 goto err

%programPath% 16 10 ZZZFS > output.txt
if not errorlevel 1 goto err

%programPath% 16 10 FFFFFFFFFFFFF > output.txt
if not errorlevel 1 goto err

echo Tests passed
exit /B 0

:err
echo Test failed
exit /B 1