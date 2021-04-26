# RISC_V_assembler
使用C實現RISC-V Assembler
## rule
1. 只能夠使用I,R,S type的指令，若為其它指令則顯示none
2. I type指令只能使用decimal
3. code必須存在txt 
4. 若全部指令都執行完成時，則會顯示done
## input
'''
    add x2,x2,x23
    addi x24,x24,2
    bne x24,x23,L2
    sw x27,0(x10)
    beq x0,x0,L1
L2: sw x1,0(x2)
L1: addi x24,x24,1
'''
## output
'''
00000001011100010000000100110011
00000000001011000000110000010011
none
00000001101101010010000000000011
none
00000000000100010010000000000011
00000000000111000000110000010011
done
'''
