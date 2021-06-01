/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perandom.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmira <ilmira@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 12:45:08 by ilmira            #+#    #+#             */
/*   Updated: 2021/03/29 17:30:41 by ilmira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_perandom4(int perandom[])
{
	perandom[94] = 54;
	perandom[95] = 65;
	perandom[96] = 25;
	perandom[97] = 63;
	perandom[98] = 161;
	perandom[99] = 1;
	perandom[100] = 216;
	perandom[101] = 80;
	perandom[102] = 73;
	perandom[103] = 209;
	perandom[104] = 76;
	perandom[105] = 132;
	perandom[106] = 187;
	perandom[107] = 208;
	perandom[108] = 89;
	perandom[109] = 18;
	perandom[110] = 169;
	perandom[111] = 200;
	perandom[112] = 196;
	perandom[113] = 135;
	perandom[114] = 130;
	perandom[115] = 116;
	perandom[116] = 188;
	init_perandom5(perandom);
}

void	init_perandom3(int perandom[])
{
	perandom[71] = 166;
	perandom[72] = 77;
	perandom[73] = 146;
	perandom[74] = 158;
	perandom[75] = 231;
	perandom[76] = 83;
	perandom[77] = 111;
	perandom[78] = 122;
	perandom[79] = 60;
	perandom[80] = 211;
	perandom[81] = 133;
	perandom[82] = 230;
	perandom[83] = 220;
	perandom[84] = 105;
	perandom[85] = 92;
	perandom[86] = 41;
	perandom[87] = 55;
	perandom[88] = 46;
	perandom[89] = 245;
	perandom[90] = 40;
	perandom[91] = 244;
	perandom[92] = 102;
	perandom[93] = 143;
	init_perandom4(perandom);
}

void	init_perandom2(int perandom[])
{
	perandom[48] = 57;
	perandom[49] = 177;
	perandom[50] = 33;
	perandom[51] = 88;
	perandom[52] = 237;
	perandom[53] = 149;
	perandom[54] = 56;
	perandom[55] = 87;
	perandom[56] = 174;
	perandom[57] = 20;
	perandom[58] = 125;
	perandom[59] = 136;
	perandom[60] = 171;
	perandom[61] = 168;
	perandom[62] = 68;
	perandom[63] = 175;
	perandom[64] = 74;
	perandom[65] = 165;
	perandom[66] = 71;
	perandom[67] = 134;
	perandom[68] = 139;
	perandom[69] = 48;
	perandom[70] = 27;
	init_perandom3(perandom);
}

void	init_perandom1(int perandom[])
{
	perandom[24] = 37;
	perandom[25] = 240;
	perandom[26] = 21;
	perandom[27] = 10;
	perandom[28] = 23;
	perandom[29] = 190;
	perandom[30] = 6;
	perandom[31] = 148;
	perandom[32] = 247;
	perandom[33] = 120;
	perandom[34] = 234;
	perandom[35] = 75;
	perandom[36] = 0;
	perandom[37] = 26;
	perandom[38] = 197;
	perandom[39] = 62;
	perandom[40] = 94;
	perandom[41] = 252;
	perandom[42] = 219;
	perandom[43] = 203;
	perandom[44] = 117;
	perandom[45] = 35;
	perandom[46] = 11;
	perandom[47] = 32;
	init_perandom2(perandom);
}

void	init_perandom(int perandom[])
{
	perandom[0] = 151;
	perandom[1] = 160;
	perandom[2] = 137;
	perandom[3] = 91;
	perandom[4] = 90;
	perandom[5] = 15;
	perandom[6] = 131;
	perandom[7] = 13;
	perandom[8] = 201;
	perandom[9] = 95;
	perandom[10] = 96;
	perandom[11] = 53;
	perandom[12] = 194;
	perandom[13] = 233;
	perandom[14] = 7;
	perandom[15] = 225;
	perandom[16] = 140;
	perandom[17] = 36;
	perandom[18] = 103;
	perandom[19] = 30;
	perandom[20] = 69;
	perandom[21] = 142;
	perandom[22] = 8;
	perandom[23] = 99;
	init_perandom1(perandom);
}
