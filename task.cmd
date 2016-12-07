:: Windows batch script for the task console app
:: TaskApp
:: CIS 22C F2016: Matthew Tso

:: Simply forward all arguments to TaskApp with `%*`
bin\TaskApp.exe --top-root %*
