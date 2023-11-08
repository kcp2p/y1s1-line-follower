/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krchuaip <krittin@42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:40:55 by krchuaip          #+#    #+#             */
/*   Updated: 2023/11/08 14:40:57 by krchuaip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAX_IR 5

/*
	First array for digital pin, second for digital value
	Use g_ to comply with generic C standards
	
	Note that some C standards apply to C++ as well,
	you don't necessary need Orthodox Canonical (C++98) in C++
	or OOP but highly recommended.
*/
static	int	g_ir[MAX_IR][2]	=	{
									{0, 0},
									{1, 0},
									{2, 0},
									{3, 0},
									{4, 0}
								};

void	setup(void)
{
	/*
		Declare an integer variable called 'i'
		and uses it to iterate through the loop until
		a certain condition is met.

		The same condition applies throughout the code
		if any condition are repeated.
	*/
	int	i;

	i = 0;
	/*
		TL;DR
		We use 9600 baud rate because our cable aren't long,
		
		Longer explanation:
		Higher baud rate requires more frequent pulse to
		both host and slave (in this case both machine can be
		identified as both host and slave), longer cable means
		longer delay electronically, so we stick to 9600 baud rate.

		It is enough to send around 10 lines of RX TX back and forth
		at one pulse. Keep in mind if it exceeds, Arduino will block
		all serial write functions until all the buffers are cleared.

		We can calculate bit rate using
	
		Bit Rate	=	Baud Rate * No. of bits

		In this case, we choose 8 bits:
		Bit Rate	=	(9600) * (8)
					=	76800
	*/
	Serial.begin(9600);

	/*
		Initialize all IR sensors as INPUT mode,
		through an iterative loop.
	*/
	while (i < MAX_IR)
	{
		pinMode(g_ir[i][0], INPUT);
		i++;
	}

}

void	loop(void)
{
	int	i;
	
	i = 0;
	Serial.print("Sensor val:");
	while (i < MAX_IR)
	{
		g_ir[i][1] = analogRead(g_ir[i][0]);
		Serial.print("\t");
		Serial.print(i+1);
		Serial.print(": ");
		Serial.print(g_ir[i][1]);
		i++;
	}
	Serial.println("");
}
