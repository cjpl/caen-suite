/////////////////////////////////////////////////////////////////////////////
// Name:        rpn_handler.cpp
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     09/01/07 16:54
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////


#if defined(__GNUG__) && !defined(__APPLE__)
#pragma implementation "rpn_handler.h"
#endif


#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "rpn_handler.h"
#include "virtual_board_channel.h"

RpnHandler::RpnHandler( VirtualBoardChannel* parent, const char *expression_def)
{
	this->m_parent= parent;
	this->m_rpn_items_array= NULL;
	this->m_tmp_rpn_items_array= NULL;
	this->m_rpn_array_alloc_size= 0;
	this->m_rpn_array_real_size= 0;
	this->m_expression_def= NULL;
	this->m_ref_channel_index= -1;
	this->Parse( expression_def);
}

RpnHandler::~RpnHandler(void)
{
	if( this->m_rpn_items_array!= NULL)
		delete[] this->m_rpn_items_array;
	if( this->m_tmp_rpn_items_array)
		delete[] this->m_tmp_rpn_items_array;
	if( this->m_expression_def)
		delete this->m_expression_def;

}

bool RpnHandler::Parse( const char *expression_def)
{
	//
	// Parse input string and build items array:
	// tokens must be ',' separated, upper or lower case, but no white space trimming will be performed !

	const int BLOCK_ALLOC_SIZE= 10;
	char* token;
	char* tmp_buff;
	this->m_ref_channel_index= -1;
	if( this->m_expression_def)
		delete this->m_expression_def;
	this->m_expression_def= new char[ strlen( expression_def)+ 1];
	tmp_buff= new char[ strlen( expression_def)+ 1];
	strcpy( this->m_expression_def, expression_def);
	strcpy( tmp_buff, expression_def);

	if( this->m_rpn_items_array!= NULL)
		delete[] this->m_rpn_items_array;

	this->m_rpn_array_alloc_size= BLOCK_ALLOC_SIZE;
	this->m_rpn_items_array= new RpnItem[ this->m_rpn_array_alloc_size];
	this->m_rpn_array_real_size= 0;

	token= strtok( tmp_buff, ",");
	while( token!= NULL)
	{
		if( this->m_rpn_array_real_size> this->m_rpn_array_alloc_size)
		{
			// Realloc
			RpnItem *tmp= new RpnItem[ this->m_rpn_array_alloc_size+ BLOCK_ALLOC_SIZE];
			memcpy( tmp, this->m_rpn_items_array, sizeof( this->m_rpn_items_array[0])* this->m_rpn_array_alloc_size);
			delete[] this->m_rpn_items_array;
			this->m_rpn_items_array= tmp;
			this->m_rpn_array_alloc_size+= BLOCK_ALLOC_SIZE;
		}

		this->m_rpn_items_array[ this->m_rpn_array_real_size].m_processed= false;
		this->m_rpn_items_array[ this->m_rpn_array_real_size].m_type= (RpnTypes)-1;
		// Check if operator or operand
		for( int i= 0; i< RPN_OPERAND_CONST; i++)
		{
			if( !stricmp( token, RpnTypesNames[ i]))
			{
				//
				// found
				this->m_rpn_items_array[ this->m_rpn_array_real_size].m_type= (RpnTypes)i;
				this->m_rpn_items_array[ this->m_rpn_array_real_size].m_value= 0;	// Don't care

				if( this->m_ref_channel_index== -1)
				{
					switch( i)
					{
					case RPN_OPERAND_CH0:		// Channel 0 Operand
					case RPN_OPERAND_CH1:		// Channel 1 Operand
					case RPN_OPERAND_CH2:		// Channel 2 Operand
					case RPN_OPERAND_CH3:		// Channel 3 Operand
					case RPN_OPERAND_CH4:		// Channel 4 Operand
					case RPN_OPERAND_CH5:		// Channel 5 Operand
					case RPN_OPERAND_CH6:		// Channel 6 Operand
					case RPN_OPERAND_CH7:		// Channel 7 Operand
						this->m_ref_channel_index= i- RPN_OPERAND_CH0;
						break;
					}
				}

				break;
			}
		}
		
		if( this->m_rpn_items_array[ this->m_rpn_array_real_size].m_type== (RpnTypes)-1)
		{
			// Literal operand type
			this->m_rpn_items_array[ this->m_rpn_array_real_size].m_type= RPN_OPERAND_CONST;
			this->m_rpn_items_array[ this->m_rpn_array_real_size].m_value= atof( token);
		}
		this->m_rpn_array_real_size++;

		token= strtok( NULL, ",");
	}
	delete tmp_buff;
	if( this->m_tmp_rpn_items_array)
		delete[] this->m_tmp_rpn_items_array;
	this->m_tmp_rpn_items_array= new RpnItem[ this->m_rpn_array_alloc_size];

	return true;
}
const char* RpnHandler::Format( )
{
	return this->m_expression_def? this->m_expression_def: "";
}
bool RpnHandler::Test( void)
{
	/*
		Just test without calculation
	*/
	return this->DoEval( NULL);
}
bool RpnHandler::Eval( double &result)
{
	return this->DoEval( &result);
}
bool RpnHandler::DoEval( double *p_result)
{
	/*
		BASIC CONCEPT
		1. No more items? jump to 10
		2. Not an Operator ? jump to 1
		3. Back search erca the first 2 unprocessed items; label them as processed, unprocessed-= 2
		4. Calculate the result and save into operator item: change item type to OPERAND_CONST
		5. Jump to 1
		10.Unprocessed!= 1 ? exit with error
		11.Back search the first (and only) unprocessed item and return result
	*/
	if( p_result)
		*p_result= 0;

	// Make an array work copy 
	memcpy( this->m_tmp_rpn_items_array, this->m_rpn_items_array, this->m_rpn_array_real_size* sizeof( this->m_rpn_items_array[ 0]));

	int current_index= 0; 
	int num_unprocessed= this->m_rpn_array_real_size;

	// Loop items
	for( current_index= 0; current_index< this->m_rpn_array_real_size; current_index++)
	{
		if( this->m_tmp_rpn_items_array[ current_index].m_processed)
			continue;
		// Check item type
		switch( this->m_tmp_rpn_items_array[ current_index].m_type)
		{
			case RPN_OPERATOR_ADD:		// Add Operator
			case RPN_OPERATOR_SUB:		// Subtract Operator
			case RPN_OPERATOR_MUL:		// Multiply Operator
			case RPN_OPERATOR_DIV:		// Divide Operator
				break;
			case RPN_OPERAND_CH0:		// Channel 0 Operand
			case RPN_OPERAND_CH1:		// Channel 1 Operand
			case RPN_OPERAND_CH2:		// Channel 2 Operand
			case RPN_OPERAND_CH3:		// Channel 3 Operand
			case RPN_OPERAND_CH4:		// Channel 4 Operand
			case RPN_OPERAND_CH5:		// Channel 5 Operand
			case RPN_OPERAND_CH6:		// Channel 6 Operand
			case RPN_OPERAND_CH7:		// Channel 7 Operand
				continue;
			case RPN_OPERAND_CONST:		// Constant value Operand : let as the least
				continue;
			default:
				// Unknown type ?
				return false;
		}
		// Operator found:
		// Get previous two unprocessed operand items
		double operands[ 2]= { 0, 0};
		int back_index= current_index- 1; 
		for( int operand= 0; operand< 2; operand++)
		{
			bool search= true;
			for( ; ( back_index>= 0)&& search; back_index--)
			{
				if( this->m_tmp_rpn_items_array[ back_index].m_processed)
					continue;
				switch( this->m_tmp_rpn_items_array[ back_index].m_type)
				{
					case RPN_OPERAND_CH0:		// Channel 0 Operand
					case RPN_OPERAND_CH1:		// Channel 1 Operand
					case RPN_OPERAND_CH2:		// Channel 2 Operand
					case RPN_OPERAND_CH3:		// Channel 3 Operand
					case RPN_OPERAND_CH4:		// Channel 4 Operand
					case RPN_OPERAND_CH5:		// Channel 5 Operand
					case RPN_OPERAND_CH6:		// Channel 6 Operand
					case RPN_OPERAND_CH7:		// Channel 7 Operand
						if( p_result)
						{
							if( !this->m_parent->GetChannelValueVolt( this->m_tmp_rpn_items_array[ back_index].m_type- RPN_OPERAND_CH0, operands[ operand]))
								return false;
							operands[ operand]*= 1000;
						}
						this->m_tmp_rpn_items_array[ back_index].m_processed= true;
						search= false;
						num_unprocessed--;
						break;
					case RPN_OPERAND_CONST:		// Constant value Operand : let as the least
						if( p_result)
						{
							operands[ operand]= this->m_tmp_rpn_items_array[ back_index].m_value;
						}
						this->m_tmp_rpn_items_array[ back_index].m_processed= true;
						search= false;
						num_unprocessed--;
						break;
					default:
						// Unknown operand ?
						return false;
				}
			}
			if( search)
			{
				// Operands not found ?
				return false;
			}
		}

		// Perform the operation
		switch( this->m_tmp_rpn_items_array[ current_index].m_type)
		{
			case RPN_OPERATOR_ADD:		// Add Operator
				if( p_result)
				{
					this->m_tmp_rpn_items_array[ current_index].m_value= operands[ 1]+ operands[ 0];
				}
				break;
			case RPN_OPERATOR_SUB:		// Subtract Operator
				if( p_result)
				{
					this->m_tmp_rpn_items_array[ current_index].m_value= operands[ 1]- operands[ 0];
				}
				break;
			case RPN_OPERATOR_MUL:		// Multiply Operator
				if( p_result)
				{
					this->m_tmp_rpn_items_array[ current_index].m_value= operands[ 1]* operands[ 0];
				}
				break;
			case RPN_OPERATOR_DIV:		// Divide Operator
				if( p_result)
				{
					if( operands[ 0]== 0)
						return false;
					this->m_tmp_rpn_items_array[ current_index].m_value= operands[ 1]/ operands[ 0];
				}
				break;
			default:
				// Unknown operator ?
				return false;
		}
		this->m_tmp_rpn_items_array[ current_index].m_type= RPN_OPERAND_CONST;
	}

	// consistency check
	if( num_unprocessed!= 1)
		return false;

	// Get the result: the only unprocessed item
	for( int back_index= this->m_rpn_array_real_size- 1; back_index>= 0; back_index--)
	{
		if( this->m_tmp_rpn_items_array[ back_index].m_processed)
			continue;
		// found
		switch( this->m_tmp_rpn_items_array[ back_index].m_type)
		{
			case RPN_OPERAND_CH0:		// Channel 0 Operand
			case RPN_OPERAND_CH1:		// Channel 1 Operand
			case RPN_OPERAND_CH2:		// Channel 2 Operand
			case RPN_OPERAND_CH3:		// Channel 3 Operand
			case RPN_OPERAND_CH4:		// Channel 4 Operand
			case RPN_OPERAND_CH5:		// Channel 5 Operand
			case RPN_OPERAND_CH6:		// Channel 6 Operand
			case RPN_OPERAND_CH7:		// Channel 7 Operand
				if( p_result)
				{
					if( !this->m_parent->GetChannelValueVolt( this->m_tmp_rpn_items_array[ back_index].m_type- RPN_OPERAND_CH0, *p_result))
						return false;
				}
				return true;
			case RPN_OPERAND_CONST:		// Constant value Operand : let as the least
				if( p_result)
				{
					*p_result= this->m_tmp_rpn_items_array[ back_index].m_value* 0.001;
				}
				return true;
			default:
				// Unknown operand ?
				return false;
		}
	}
	return true;
}

unsigned int RpnHandler::GetBufferCount( void)
{
	if( this->m_ref_channel_index< 0)
		return (unsigned int)-1;
	unsigned int value= 0;
	if( !this->m_parent->GetChannelBufferCount( this->m_ref_channel_index, value))
		return (unsigned int)-1;
	return value;
}

