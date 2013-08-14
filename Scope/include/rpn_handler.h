/////////////////////////////////////////////////////////////////////////////
// Name:        rpn_handler.h
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     09/01/07 16:54
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _RPN_HANDLER_H_
#define _RPN_HANDLER_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "rpn_handler.h"
#endif

class VirtualBoardChannel;
/*!
 * Includes
 */
typedef enum
{
	RPN_OPERATOR_ADD= 0,		// Add Operator
	RPN_OPERATOR_SUB,			// Subtract Operator
	RPN_OPERATOR_MUL,			// Multiply Operator
	RPN_OPERATOR_DIV,			// Divide Operator

	RPN_OPERAND_CH0,			// Channel 0 Operand
	RPN_OPERAND_CH1,			// Channel 1 Operand
	RPN_OPERAND_CH2,			// Channel 2 Operand
	RPN_OPERAND_CH3,			// Channel 3 Operand
	RPN_OPERAND_CH4,			// Channel 4 Operand
	RPN_OPERAND_CH5,			// Channel 5 Operand
	RPN_OPERAND_CH6,			// Channel 6 Operand
	RPN_OPERAND_CH7,			// Channel 7 Operand

	RPN_OPERAND_CONST,			// Constant value Operand : let as the least
} RpnTypes;

#ifndef LPCSTR 
typedef const char* LPCSTR;
#endif
//
// Rpn name s for string parsing
const LPCSTR RpnTypesNames[]=
{
	"ADD",			// Add Operator
	"SUB",			// Subtract Operator
	"MUL",			// Multiply Operator
	"DIV",			// Divide Operator
	
	"CH0",			// Channel 1 Operand
	"CH1",			// Channel 2 Operand
	"CH2",			// Channel 3 Operand
	"CH3",			// Channel 4 Operand
	"CH4",			// Channel 5 Operand
	"CH5",			// Channel 6 Operand
	"CH6",			// Channel 7 Operand
	"CH7",			// Channel 7 Operand

	// Any other undefined name will be handled as CONST operand value
};
struct RpnItem
{
	bool m_processed;
	double m_value;
	RpnTypes m_type;
};

class RpnHandler
{
public:
	RpnHandler( VirtualBoardChannel* parent, const char *expression_def);
	~RpnHandler( void);

	bool Parse( const char *expression_def);
	const char* Format( void);
	bool Test( void);
	bool Eval( double &result);
	unsigned int GetBufferCount( void);
protected:
	RpnItem* m_rpn_items_array;
	RpnItem* m_tmp_rpn_items_array;
	int m_rpn_array_alloc_size;
	int m_rpn_array_real_size;
	char* m_expression_def;
	bool DoEval( double *p_result);
	VirtualBoardChannel* m_parent;
	int m_ref_channel_index;
	
};


#endif	// _RPN_HANDLER_H_

