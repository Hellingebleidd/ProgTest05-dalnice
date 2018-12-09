@ set testPrg= ..\cmake-build-debug\ProgTest05_dalnice.exe
@ echo Testy 0000-0013. Testovany program = %testPrg%

@ %testPrg% < 0000_in.txt > 0000_out_zz.txt
@ %testPrg% < 0001_in.txt > 0001_out_zz.txt
@ %testPrg% < 0002_in.txt > 0002_out_zz.txt
@ %testPrg% < 0003_in.txt > 0003_out_zz.txt
@ %testPrg% < 0003_in.txt > 0003_out_zz.txt
@ %testPrg% < 0004_in.txt > 0004_out_zz.txt
@ %testPrg% < 0005_in.txt > 0005_out_zz.txt


@ fc 0000_out_zz.txt 0000_out_win.txt > null && Echo 0000 ok || fc 0000_out_zz.txt 0000_out_win.txt
@ fc 0001_out_zz.txt 0001_out_win.txt > null && Echo 0001 ok || fc 0001_out_zz.txt 0001_out_win.txt
@ fc 0002_out_zz.txt 0002_out_win.txt > null && Echo 0002 ok || fc 0002_out_zz.txt 0002_out_win.txt
@ fc 0003_out_zz.txt 0003_out_win.txt > null && Echo 0003 ok || fc 0003_out_zz.txt 0003_out_win.txt
@ fc 0004_out_zz.txt 0004_out_win.txt > null && Echo 0004 ok || fc 0004_out_zz.txt 0004_out_win.txt
@ fc 0005_out_zz.txt 0005_out_win.txt > null && Echo 0005 ok || fc 0005_out_zz.txt 0005_out_win.txt
