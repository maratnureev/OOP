SET programPath="%~1"

%programPath% input.txt "output.txt" "Replace" "VALID" || goto err
fc "expected.txt" "output.txt" || goto err

%programPath% input1.txt "output.txt" "test" "VALID" || goto err
fc "expected1.txt" "output.txt" || goto err

%programPath% input2.txt "output.txt" "a" "b" || goto err
fc "expected2.txt" "output.txt" || goto err

%programPath% input3.txt "output.txt" "1" "?" || goto err
fc "expected3.txt" "output.txt" || goto err

%programPath% input4.txt "output.txt" " " "5" || goto err
fc "expected4.txt" "output.txt" || goto err

%programPath% input4.txt "output.txt" "" "5" || goto err
fc "expected5.txt" "output.txt" || goto err

%programPath% input6.txt "non-existing-file.txt" "1" "2" > output.txt
if not errorlevel 1 goto err

%programPath% input3.txt "%programPath%" "1" "2" > output.txt
if not errorlevel 1 goto err

echo Tests complited
exit /B 0

:err
echo  Test failed
exit /B 1