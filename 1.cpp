#include<stdio.h>
#include<cstdlib>
#include<sstream>
#include<string>
#include<iostream>
#include<assert.h>
#include<stdbool.h>

using namespace std;
char machine_code_note[200][128];
char label[200][20];
int label1_addr, label2_addr, label3_addr, label4_addr, label5_addr;
int label_count;
int k = 0;

//-----------------------------define instruction word-----------------
std::string label_1;
std::string label_2;
std::string label_3;
std::string label_4;
std::string label_5;



// [ R_type_instruction ]
std::string ADD("add");
std::string SUB("sub");
std::string SLL("sll");
std::string SLT("slt");
std::string SLTU("sltu");
std::string XOR("xor");
std::string SRL("srl");
std::string SRA("sra");
std::string OR("or");
std::string AND("and");
std::string idx;
// [ I_type_instruction ]
std::string JALR("jalr");
std::string LB("lb");
std::string LH("lh");
std::string LW("lw");
std::string LBU("lbu");
std::string LHU("lhu");
std::string ADDI("addi");
std::string SLTI("slti");
std::string SLTIU("sltiu");
std::string XORI("xori");
std::string ORI("ori");
std::string ANDI("andiI");
// [ S_type_instruction ]
std::string SB("sb");
std::string SH("sh");
std::string SW("sw");
// [ U_type_instruction ]
std::string LUI("lui");
std::string AUIPC("auipc");
// [ SB_type_instruction ]
std::string BEQ("beq");
std::string BNE("bne");
std::string BLT("blt");
std::string BGE("bce");
std::string BLTU("bltu");
std::string BGEU("bgeq");
//-------------------------------------function
void dec_to_bin(int a, char b[],int n);

void main(void)
{
	int instruction_addr = 0;
	int label_addr[200][4];
	std::string str;

	while (str != "end") {	
		
		getline(cin, str);
		//----------------------------------------detect_label
		int i = 0;
		while (str[i] != '\0') {
			if (str[i] == ':') {
				label_count += 1;
				for (int index = 0; index < i; index++) {
					label[label_count][index] = str[index];
				}
				switch(label_count) {
				case 1:
					label_1 = label[label_count];
					label1_addr = instruction_addr;
					break;
				case 2:
					label_2 = label[label_count];
					label2_addr = instruction_addr;					
					break;
				case 3:
					label_3 = label[label_count];
					label3_addr = instruction_addr;
				case 4:
					label_4 = label[label_count];
					label4_addr = instruction_addr;
				case 5:
					label_5 = label[label_count];
					label5_addr = instruction_addr;
				default:
					break;			
				}
			}
			i += 1;
		}

		//|----------------------------------------------------|
		//|----------------I_type_instructions-----------------|
		//|----------------------------------------------------|
		if (str.find(JALR) != string::npos ||
		str.find(LB) != string::npos ||
		str.find(LH) != string::npos ||
		str.find(LW) != string::npos ||
		str.find(LBU) != string::npos ||
		str.find(LHU) != string::npos ||
		str.find(ADDI) != string::npos ||
		str.find(SLTI) != string::npos ||
		str.find(SLTIU) != string::npos ||
		str.find(XORI) != string::npos ||
		str.find(ORI) != string::npos ||
		str.find(ANDI) != string::npos) {
		int i = 0;
		int X_recorder = 0;
		char rd_I[3];
		char rs_1_I[3];
		char rd_b_I[5];
		char rs1_b_I[5];
		char funct3_I[4];
		char imme_I[5];
		char imme_b_I[12];
		char opcode_I[8];

		//---------------------------------------verify_register---------------
		if (str.find(JALR) != string::npos ||
			str.find(ADDI) != string::npos ||
			str.find(SLTI) != string::npos ||
			str.find(SLTIU) != string::npos ||
			str.find(XORI) != string::npos ||
			str.find(ORI) != string::npos ||
			str.find(ANDI) != string::npos) {
			while (str[i] != '\0') {
				i = i + 1;
				if (str[i] == 'x' && X_recorder == 0) {
					if (str[i + 2] == ',') {
						rd_I[0] = str[i + 1];
						//cout << rd[0] << endl;
						X_recorder += 1;
						continue;
					}
					else {
						rd_I[0] = str[i + 1];
						rd_I[1] = str[i + 2];
						//cout << str[i + 1] << str[i + 2] << endl;
						X_recorder += 1;
						continue;
					}
				}
				if (str[i] == 'x' && X_recorder == 1) {
					if (str[i + 2] == ',') {
						rs_1_I[0] = str[i + 1];
						//cout << rs_1_R[0] << endl;
						X_recorder += 1;
						continue;
					}
					else {
						rs_1_I[0] = str[i + 1];
						rs_1_I[1] = str[i + 2];
						//cout << str[i + 1] << str[i + 2] << endl;
						X_recorder += 1;
						continue;
					}
				}
			}
			if (str.find(LB) != string::npos ||
				str.find(LH) != string::npos ||
				str.find(LW) != string::npos ||
				str.find(LBU) != string::npos ||
				str.find(LHU) != string::npos  ) {
				i = 0;
				X_recorder = 0;
				while (str[i] != '\0') {
					i = i + 1;
					if (str[i] == 'x' && X_recorder == 0) {
						if (str[i + 2] == ',') {
							rd_I[0] = str[i + 1];
							//cout << rd[0] << endl;
							X_recorder += 1;
							continue;
						}
						else {
							rd_I[0] = str[i + 1];
							rd_I[1] = str[i + 2];
							//cout << str[i + 1] << str[i + 2] << endl;
							X_recorder += 1;
							continue;
						}
					}
					if (str[i] == 'x' && X_recorder == 1) {
						if (str[i + 2] == ')') {
							rs_1_I[0] = str[i + 1];
							//cout << rs_1_R[0] << endl;
							X_recorder += 1;
							continue;
						}
						else {
							rs_1_I[0] = str[i + 1];
							rs_1_I[1] = str[i + 2];
							//cout << str[i + 1] << str[i + 2] << endl;
							X_recorder += 1;
							continue;
						}
					}


				}
				

			}


		}
		//------------------------------------------------verify_OP_code---&&---catch_immediate_value
		if (str.find(JALR) != string::npos) {
			opcode_I[0] = '1';
			opcode_I[1] = '1';
			opcode_I[2] = '0';
			opcode_I[3] = '0';
			opcode_I[4] = '1';
			opcode_I[5] = '1';
			opcode_I[6] = '1';
			i = 0;
			int comma = 0;
			int index = 0;
			while (str[i] != '\0') {
				i = i + 1;
				if (str[i] == ',') {
					comma = comma + 1;
					continue;
				}
				if (comma == 2) {
					imme_I[index] = str[i];
					index = index + 1;
				}
			}

		}
		else if (str.find(LB) != string::npos ||
			str.find(LH) != string::npos ||
			str.find(LW) != string::npos ||
			str.find(LBU) != string::npos ||
			str.find(LHU) != string::npos) {
			opcode_I[0] = '0';
			opcode_I[1] = '0';
			opcode_I[2] = '0';
			opcode_I[3] = '0';
			opcode_I[4] = '0';
			opcode_I[5] = '1';
			opcode_I[6] = '1';
			int i = 0;
			int index = 0;
			int comma = 0;
			while (str[i] != '\0') {
				i = i + 1;
				if (str[i] == ',')
					comma = comma + 1;
				else if (str[i] == '(')
					break;
				else if (comma == 1) {
					imme_I[index] = str[i];
					index = index + 1;
				}
			}
		}
		else {
			opcode_I[0] = '0';
			opcode_I[1] = '0';
			opcode_I[2] = '1';
			opcode_I[3] = '0';
			opcode_I[4] = '0';
			opcode_I[5] = '1';
			opcode_I[6] = '1';
			i = 0;
			int comma = 0;
			int index = 0;
			while (str[i] != '\0') {
				i = i + 1;
				if (str[i] == ',') {
					comma = comma + 1;
					continue;
				}
				if (comma == 2) {
					imme_I[index] = str[i];
					index = index + 1;
				}
			}
		}

		//---------------------------------------------------transfer imme_I_to_binery
		int imme_int_I = atoi(imme_I);
		dec_to_bin(imme_int_I, imme_b_I, 12);
		//---------------------------------------------------transfer register_to_bineray
		int rd_int_I = atoi(rd_I);
		int rs1_int_I = atoi(rs_1_I);
		dec_to_bin(rd_int_I, rd_b_I, 5);
		dec_to_bin(rs1_int_I, rs1_b_I, 5);

		//--------------------------------------------------verify_funct3
		if (str.find(LHU) != string::npos) {
			funct3_I[0] = '1';
			funct3_I[1] = '0';
			funct3_I[2] = '1';
		}
		else if (str.find(LH) != string::npos) {
			funct3_I[0] = '0';
			funct3_I[1] = '0';
			funct3_I[2] = '1';
		}
		else if (str.find(LBU) != string::npos ||
			str.find(XORI) != string::npos) {
			funct3_I[0] = '1';
			funct3_I[1] = '0';
			funct3_I[2] = '0';
		}
		else if (str.find(JALR) != string::npos ||
			str.find(ADDI) != string::npos ||
			str.find(LB) != string::npos) {
			funct3_I[0] = '0';
			funct3_I[1] = '0';
			funct3_I[2] = '0';
		}
		else if (str.find(SLTIU) != string::npos) {
			funct3_I[0] = '0';
			funct3_I[1] = '1';
			funct3_I[2] = '1';
		}
		else if (str.find(LW) != string::npos ||
			str.find(SLTI) != string::npos) {
			funct3_I[0] = '0';
			funct3_I[1] = '1';
			funct3_I[2] = '0';
		}
		else if (str.find(ORI) != string::npos) {
			funct3_I[0] = '1';
			funct3_I[1] = '1';
			funct3_I[2] = '0';
		}
		else if (str.find(ANDI) != string::npos) {
			funct3_I[0] = '1';
			funct3_I[1] = '1';
			funct3_I[2] = '1';
		}
		//---------------------------------------assign_machine_code
		machine_code_note[k][0] = imme_b_I[0];
		machine_code_note[k][1] = imme_b_I[1];
		machine_code_note[k][2] = imme_b_I[2];
		machine_code_note[k][3] = imme_b_I[3];
		machine_code_note[k][4] = imme_b_I[4];
		machine_code_note[k][5] = imme_b_I[5];
		machine_code_note[k][6] = imme_b_I[6];
		machine_code_note[k][7] = imme_b_I[7];
		machine_code_note[k][8] = imme_b_I[8];
		machine_code_note[k][9] = imme_b_I[9];
		machine_code_note[k][10] = imme_b_I[10];
		machine_code_note[k][11] = imme_b_I[11];

		machine_code_note[k][12] = rs1_b_I[0];
		machine_code_note[k][13] = rs1_b_I[1];
		machine_code_note[k][14] = rs1_b_I[2];
		machine_code_note[k][15] = rs1_b_I[3];
		machine_code_note[k][16] = rs1_b_I[4];

		machine_code_note[k][17] = funct3_I[0];
		machine_code_note[k][18] = funct3_I[1];
		machine_code_note[k][19] = funct3_I[2];

		machine_code_note[k][20] = rd_b_I[0];
		machine_code_note[k][21] = rd_b_I[1];
		machine_code_note[k][22] = rd_b_I[2];
		machine_code_note[k][23] = rd_b_I[3];
		machine_code_note[k][24] = rd_b_I[4];

		machine_code_note[k][25] = opcode_I[0];
		machine_code_note[k][26] = opcode_I[1];
		machine_code_note[k][27] = opcode_I[2];
		machine_code_note[k][28] = opcode_I[3];
		machine_code_note[k][29] = opcode_I[4];
		machine_code_note[k][30] = opcode_I[5];
		machine_code_note[k][31] = opcode_I[6];
		}


		//|----------------------------------------------------|
		//|----------------R_type_instructions-----------------|
		//|----------------------------------------------------|
		else if (str.find(ADD) != string::npos ||
			str.find(SUB) != string::npos ||
			str.find(SLL) != string::npos ||
			str.find(SLT) != string::npos ||
			str.find(SLTU) != string::npos ||
			str.find(XOR) != string::npos ||
			str.find(SRL) != string::npos ||
			str.find(SRA) != string::npos ||
			str.find(OR) != string::npos ||
			str.find(AND) != string::npos ) {
			int i = 0;
			int X_recorder = 0;  //recorder x_register
			char rd_R[3];
			char rs_1_R[3];
			char rs_2_R[3];
			char rd_b_R[5];
			char rs1_b_R[5];
			char rs2_b_R[5];
			//int rd,rs1,rs2;			
			char opcode_R[8] = "0110011";
			char funct5_R[6];
			char funct2_R[3] = "00";
			char funct3_R[4];
			//---------------------------------------verify_register---------------
			while (str[i] != '\0') {
				i = i + 1;
 				if (str[i] == 'x' && X_recorder == 0) {
					if (str[i + 2] == ',') {
						rd_R[0] = str[i + 1];
						//cout << rd[0] << endl;
						X_recorder += 1;
						continue;
					}
					else  { 
						rd_R[0] = str[i + 1];
						rd_R[1] = str[i + 2];
						//cout << str[i + 1] << str[i + 2] << endl;
						X_recorder += 1;
						continue;
					}
				}
				if (str[i] == 'x' && X_recorder == 1) {
					if (str[i + 2] == ',') {
						rs_1_R[0] = str[i + 1];
						//cout << rs_1_R[0] << endl;
						X_recorder += 1;
						continue;
					}
					else {
						rs_1_R[0] = str[i + 1];
						rs_1_R[1] = str[i + 2];
						//cout << str[i + 1] << str[i + 2] << endl;
						X_recorder += 1;
						continue;
					}
				}
				if (str[i] == 'x' && X_recorder == 2) {
					if (str[i + 2] == ',') {
						rs_2_R[0] = str[i + 1];
						//cout << rs_2[0] << endl;
						continue;
					}
					else {
						rs_2_R[0] = str[i + 1];
						rs_2_R[1] = str[i + 2];
						//cout << str[i + 1] << str[i + 2] << endl;	
						continue;
					}
				}

				
			}
			int rd_int_I = atoi(rd_R);
			int rs1_int_I = atoi(rs_1_R);
			int rs2_int_I = atoi(rs_2_R);			
			dec_to_bin(rd_int_I, rd_b_R , 5);
			dec_to_bin(rs1_int_I, rs1_b_R , 5);
			dec_to_bin(rs2_int_I, rs2_b_R , 5);
			//itoa(rd_int, rd_b, 2);
			//itoa(rs1_int, rs1_b_R, 2);
			//itoa(rs2_int, rs2_b_R, 2);
			

			//-------------------------------------------------------------verfy_funct5_R
			if (str.find(SUB) != string::npos ||
				str.find(SRA) != string::npos) {
				funct5_R[0] = '0';
				funct5_R[1] = '0';
				funct5_R[2] = '1';
				funct5_R[3] = '0';
				funct5_R[4] = '0';				
			}
			else
			{
				funct5_R[0] = '0';
				funct5_R[1] = '0';
				funct5_R[2] = '0';
				funct5_R[3] = '0';
				funct5_R[4] = '0';
			}
			//--------------------------------------------verify_func3
			if( str.find(ADD) != string::npos ||
				str.find(SUB) != string::npos ){
				funct3_R[0] = '0';
				funct3_R[1] = '0';
				funct3_R[2] = '0';
			}
			else if (str.find(SLL) != string::npos ) {
				funct3_R[0] = '0';
				funct3_R[1] = '0';
				funct3_R[2] = '1';
			}
			else if (str.find(SLT) != string::npos ) {
				funct3_R[0] = '0';
				funct3_R[1] = '1';
				funct3_R[2] = '0';
			}
			else if (str.find(SLTU) != string::npos ) {
				funct3_R[0] = '0';
				funct3_R[1] = '1';
				funct3_R[2] = '1';
			}
			else if (str.find(XOR) != string::npos ) {
				funct3_R[0] = '1';
				funct3_R[1] = '0';
				funct3_R[2] = '0';
			}
			else if (str.find(SRL) != string::npos ||
					 str.find(SRA) != string::npos ) {
				funct3_R[0] = '1';
				funct3_R[1] = '0';
				funct3_R[2] = '1';
			}
			else if (str.find(OR) != string::npos) {
				funct3_R[0] = '1';
				funct3_R[1] = '1';
				funct3_R[2] = '0';
			}
			else if (str.find(AND) != string::npos) {
				funct3_R[0] = '1';
				funct3_R[1] = '1';
				funct3_R[2] = '1';
			}
			//---------------------------------------assign_machine_code
			machine_code_note[k][0] = funct5_R[0];
			machine_code_note[k][1] = funct5_R[1];
			machine_code_note[k][2] = funct5_R[2];
			machine_code_note[k][3] = funct5_R[3];
			machine_code_note[k][4] = funct5_R[4];

			machine_code_note[k][5] = funct2_R[0];
			machine_code_note[k][6] = funct2_R[1];

			machine_code_note[k][7] = rs2_b_R[0];
			machine_code_note[k][8] = rs2_b_R[1];
			machine_code_note[k][9] = rs2_b_R[2];
			machine_code_note[k][10] = rs2_b_R[3];
			machine_code_note[k][11] = rs2_b_R[4];

			machine_code_note[k][12] = rs1_b_R[0];
			machine_code_note[k][13] = rs1_b_R[1];
			machine_code_note[k][14] = rs1_b_R[2];
			machine_code_note[k][15] = rs1_b_R[3];
			machine_code_note[k][16] = rs1_b_R[4];

			machine_code_note[k][17] = funct3_R[0];
			machine_code_note[k][18] = funct3_R[1];
			machine_code_note[k][19] = funct3_R[2];

			machine_code_note[k][20] = rd_b_R[0];
			machine_code_note[k][21] = rd_b_R[1];
			machine_code_note[k][22] = rd_b_R[2];
			machine_code_note[k][23] = rd_b_R[3];
			machine_code_note[k][24] = rd_b_R[4];

			machine_code_note[k][25] = opcode_R[0];
			machine_code_note[k][26] = opcode_R[1];
			machine_code_note[k][27] = opcode_R[2];
			machine_code_note[k][28] = opcode_R[3];
			machine_code_note[k][29] = opcode_R[4];
			machine_code_note[k][30] = opcode_R[5];
			machine_code_note[k][31] = opcode_R[6];			
		}	
		//|----------------------------------------------------|
		//|----------------S_type_instructions-----------------|
		//|----------------------------------------------------|
		else if (str.find(SB) != string::npos ||
			 str.find(SH) != string::npos ||
			 str.find(SW) != string::npos) {
			 int i = 0;
			 int X_recorder = 0;
			 char rs_1_S[3]="";
			 char rs_2_S[3]="";
			 char rs1_b_S[5];
			 char rs2_b_S[5];
			 char funct3_S[4];
			 char imme_S[3];
			 char imme_b_S[5];
			 char opcode_S[8] = "0100011";
			 //---------------------------------------verify_register---------------
			 while (str[i] != '\0') {
				 i = i + 1;
				 if (str[i] == 'x' && X_recorder == 0) {
					 if (str[i + 2] == ',') {
						 rs_2_S[0] = str[i + 1];
						 //cout << rd[0] << endl;
						 X_recorder += 1;
						 continue;
					 }
					 else {
						 rs_2_S[0] = str[i + 1];
						 rs_2_S[1] = str[i + 2];
						 //cout << str[i + 1] << str[i + 2] << endl;
						 X_recorder += 1;
						 continue;
					 }
				 }
				 if (str[i] == 'x' && X_recorder == 1) {
					 if (str[i + 2] == ')') {
						 rs_1_S[0] = str[i + 1];
						 //cout << rs_1_R[0] << endl;
						 X_recorder += 1;
						 continue;
					 }
					 else {
						 rs_1_S[0] = str[i + 1];
						 rs_1_S[1] = str[i + 2];
						 //cout << str[i + 1] << str[i + 2] << endl;
						 X_recorder += 1;
						 continue;
					 }
				 }


			 }
			 //------------------------------------------verify_funct3
			 if (str.find(SB) != string::npos) {
				 funct3_S[0] = '0';
				 funct3_S[1] = '0';
				 funct3_S[2] = '0';
			 }
			 else if (str.find(SH) != string::npos) {
				 funct3_S[0] = '0';
				 funct3_S[1] = '0';
				 funct3_S[2] = '1';
			 }
			 else if (str.find(SW) != string::npos) {
				 funct3_S[0] = '0';
				 funct3_S[1] = '1';
				 funct3_S[2] = '0';
			 }

			 //-----------------------------------------------catch_immediate_value
			 i = 0;
			 int index = 0;
			 int parentheses = 0;
			 while (str[i] != '\0') {
				 i = i + 1;
				 if (str[i] == '(') {
					 parentheses = 1;
					 continue;
				 }
				 if (parentheses == 1) {
					 if (str[i] == ')')
						 break;
					 imme_S[index] = str[i];
					 index = index + 1;
				 }
			 }
				 //------------------------------------------transfer_dec_to_binery
				 int rs1_int_S = atoi(rs_1_S);
				 dec_to_bin(rs1_int_S, rs1_b_S, 5);
				 int rs2_int_S = atoi(rs_2_S);
				 dec_to_bin(rs2_int_S, rs2_b_S, 5);
				 int imme_int_S = atoi(imme_S);
				 dec_to_bin(imme_int_S, imme_b_S, 12);	 
			 
			 //-------------------------------------------------assign_machine_code
			 machine_code_note[k][0] = imme_b_S[0];
			 machine_code_note[k][1] = imme_b_S[1];
			 machine_code_note[k][2] = imme_b_S[2];
			 machine_code_note[k][3] = imme_b_S[3];
			 machine_code_note[k][4] = imme_b_S[4];
			 machine_code_note[k][5] = imme_b_S[5];
			 machine_code_note[k][6] = imme_b_S[6];

			 machine_code_note[k][7] = rs2_b_S[0];
			 machine_code_note[k][8] = rs2_b_S[1];
			 machine_code_note[k][9] = rs2_b_S[2];
			 machine_code_note[k][10] = rs2_b_S[3];
			 machine_code_note[k][11] = rs2_b_S[4];

			 machine_code_note[k][12] = rs1_b_S[0];
			 machine_code_note[k][13] = rs1_b_S[1];
			 machine_code_note[k][14] = rs1_b_S[2];
			 machine_code_note[k][15] = rs1_b_S[3];
			 machine_code_note[k][16] = rs1_b_S[4];

			 machine_code_note[k][17] = funct3_S[0];
			 machine_code_note[k][18] = funct3_S[1];
			 machine_code_note[k][19] = funct3_S[2];

			 machine_code_note[k][20] = imme_b_S[7];
			 machine_code_note[k][21] = imme_b_S[8];
			 machine_code_note[k][22] = imme_b_S[9];
			 machine_code_note[k][23] = imme_b_S[10];
			 machine_code_note[k][24] = imme_b_S[11];

			 machine_code_note[k][25] = opcode_S[0];
			 machine_code_note[k][26] = opcode_S[1];
			 machine_code_note[k][27] = opcode_S[2];
			 machine_code_note[k][28] = opcode_S[3];
			 machine_code_note[k][29] = opcode_S[4];
			 machine_code_note[k][30] = opcode_S[5];
			 machine_code_note[k][31] = opcode_S[6];
		}
		//|----------------------------------------------------|
		//|----------------U_type_instructions-----------------|
		//|----------------------------------------------------|
		else if (str.find(LUI) != string::npos ||
			str.find(AUIPC) != string::npos) {
			int i = 0;
			//------------------------------------------verify_register			
		}
		

		//|----------------------------------------------------|
		//|----------------SB_type_instructions----------------|
		//|----------------------------------------------------|

		else if (str.find(BEQ) != string::npos ||
			str.find(BNE) != string::npos ||
			str.find(BLT) != string::npos ||
			str.find(BGE) != string::npos ||
			str.find(BLTU) != string::npos ||
			str.find(BGEU) != string::npos) {
			int i = 0;
			int X_recorder = 0;
			char rs_1_SB[3];
			char rs_2_SB[3];
			char rs1_b_SB[5];
			char rs2_b_SB[5];
			char funct3_SB[4];
			char opcode_SB[8] ="1100011";
			int offset;
			char offset_bibery_SB[14];

			//--------------------------------------------------verify_register
			while (str[i] != '\0') {
				i = i + 1;
				if (str[i] == 'x' && X_recorder == 0) {
					if (str[i + 2] == ',') {
						rs_1_SB[0] = str[i + 1];
						//cout << rd[0] << endl;
						X_recorder += 1;
						continue;
					}
					else {
						rs_1_SB[0] = str[i + 1];
						rs_1_SB[1] = str[i + 2];
						//cout << str[i + 1] << str[i + 2] << endl;
						X_recorder += 1;
						continue;
					}
				}
				if (str[i] == 'x' && X_recorder == 1) {
					if (str[i + 2] == ',') {
						rs_2_SB[0] = str[i + 1];
						//cout << rs_1_R[0] << endl;
						X_recorder += 1;
						continue;
					}
					else {
						rs_2_SB[0] = str[i + 1];
						rs_2_SB[1] = str[i + 2];
						//cout << str[i + 1] << str[i + 2] << endl;
						X_recorder += 1;
						continue;
					}
				}				
			}
			//-----------------------------------------------------------------verify_funct3
			if (str.find(BEQ) != string::npos) {
				funct3_SB[0] = '0';
				funct3_SB[1] = '0';
				funct3_SB[2] = '0';
			}
			else if (str.find(BNE) != string::npos) {
				funct3_SB[0] = '0';
				funct3_SB[1] = '0';
				funct3_SB[2] = '1';
			}
			else if (str.find(BLTU) != string::npos) {
				funct3_SB[0] = '1';
				funct3_SB[1] = '1';
				funct3_SB[2] = '0';
			}
			else if (str.find(BGEU) != string::npos) {
				funct3_SB[0] = '1';
				funct3_SB[1] = '1';
				funct3_SB[2] = '1';
			}
			else if (str.find(BLT) != string::npos) {
				funct3_SB[0] = '1';
				funct3_SB[1] = '0';
				funct3_SB[2] = '0';
			}
			//------------------------------------------------------verify_label_to_jump
			if (str.find(label_1) != string::npos) {
				offset = instruction_addr - label1_addr;
			}
			if (str.find(label_2) != string::npos) {
				offset = instruction_addr - label2_addr;
			}
			if (str.find(label_3) != string::npos) {
				offset = instruction_addr - label3_addr;
			}
			if (str.find(label_4) != string::npos) {
				offset = instruction_addr - label4_addr;
			}
			if (str.find(label_5) != string::npos) {
				offset = instruction_addr - label5_addr;
			}
			int rs1_int_SB = atoi(rs_1_SB);
			int rs2_int_SB = atoi(rs_2_SB);
			dec_to_bin(rs1_int_SB, rs1_b_SB, 5);
			dec_to_bin(rs2_int_SB, rs2_b_SB, 5);
			dec_to_bin(offset, offset_bibery_SB, 13);

			//--------------------------------------------transfer_to_machine_code
			machine_code_note[k][0] = offset_bibery_SB[12];
			machine_code_note[k][1] = offset_bibery_SB[10];
			machine_code_note[k][2] = offset_bibery_SB[9];
			machine_code_note[k][3] = offset_bibery_SB[8];
			machine_code_note[k][4] = offset_bibery_SB[7];
			machine_code_note[k][5] = offset_bibery_SB[6];
			machine_code_note[k][6] = offset_bibery_SB[5];

			machine_code_note[k][7] = rs2_b_SB[0];
			machine_code_note[k][8] = rs2_b_SB[1];
			machine_code_note[k][9] = rs2_b_SB[2];
			machine_code_note[k][10] = rs2_b_SB[3];
			machine_code_note[k][11] = rs2_b_SB[4];

			machine_code_note[k][12] = rs1_b_SB[0];
			machine_code_note[k][13] = rs1_b_SB[1];
			machine_code_note[k][14] = rs1_b_SB[2];
			machine_code_note[k][15] = rs1_b_SB[3];
			machine_code_note[k][16] = rs1_b_SB[4];

			machine_code_note[k][17] = funct3_SB[0];
			machine_code_note[k][18] = funct3_SB[1];
			machine_code_note[k][19] = funct3_SB[2];

			machine_code_note[k][20] = offset_bibery_SB[4];
			machine_code_note[k][21] = offset_bibery_SB[3];
			machine_code_note[k][22] = offset_bibery_SB[2];
			machine_code_note[k][23] = offset_bibery_SB[1];
			machine_code_note[k][24] = offset_bibery_SB[11];

			machine_code_note[k][25] = opcode_SB[0];
			machine_code_note[k][26] = opcode_SB[1];
			machine_code_note[k][27] = opcode_SB[2];
			machine_code_note[k][28] = opcode_SB[3];
			machine_code_note[k][29] = opcode_SB[4];
			machine_code_note[k][30] = opcode_SB[5];
			machine_code_note[k][31] = opcode_SB[6];		
		}




		k = k + 1;
		instruction_addr = instruction_addr + 8;
	}	
	for (int j = 0; j <= k; j += 1) {
		cout << machine_code_note[j] << endl;
	}
}



void dec_to_bin(int a , char b[] , int n) {
	int num;
	int recorder = a;
	
	int binary[32];
	if (a < 0)
		a = -a;

	for (int i = n - 1; i >= 0; i -= 1) {
		num = a % 2;
		binary[i] = num;
		b[i] = num + '0';
		a = a / 2;
	}
	
	if (recorder < 0) {
		for (int i = 0; i < n; i++) {
			if (binary[i] == 0)
				binary[i] = 1;				
			else
				binary[i] = 0;				
		}

		for (int i = n-1; i > 0 ; i--) {
			if (binary[i] == 1) {
				binary[i] = 0;
				continue;
			}
			else
				binary[i] = 1;
				break;
		}
		for (int i = 0; i < n; i++) {
			b[i] = binary[i] + '0';
		}
	

	}			
}




