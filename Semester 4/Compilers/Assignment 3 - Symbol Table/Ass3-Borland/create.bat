ass3 ass3r.pls > ass3r.out
ass3 ass3m.pls -stz 10 > ass3m_stz10.out
ass3 ass3m.pls > ass3m.out
ass3 ass3r.pls -sts:A > ass3r_stsa.out

diff ass3r.out ../Assignment3MPTF/ass3r.out
diff ass3m_stz10.out ../Assignment3MPTF/ass3m_stz10.out
diff ass3m.out ../Assignment3MPTF/ass3m.out
diff ass3r_stsa.out ../Assignment3MPTF/ass3r_stsa.out
diff $stable.ste ../Assignment3MPTF/$stable.out

pause
