#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"

#ifndef BUILDTREE_OFF
TreeNode * helper(Scanner * s){
	Token t = nextToken(s);
	if(t.type == T_VAL)
	{
		TreeNode * valuetree = buildTreeNode(t);
		return valuetree;
	}
	else if(t.type == T_LPAREN)
	{
		TreeNode * left = helper(s);
		Token op = nextToken(s);
		//check if op is +-*/
		if(op.type == T_ADD || op.type == T_SUB || op.type == T_MUL || op.type == T_DIV)
		{
			TreeNode * right = helper(s);
			Token Rt = nextToken(s);
			if (Rt.type == T_RPAREN)
			{
				TreeNode * node = buildTreeNode(op);
				node->left = left;
				node->right = right;
				return node;
			}
			else
			{
				exit(1);
			}
		}
		else
		{
			exit(1);
		}
	}
	else
	{
		exit(1);
	}
}

TreeNode * buildExpressionTree(Scanner * s) {
	TreeNode * treebuild = helper(s);
	Token next = nextToken(s); 
	if (next.type != T_EOF)
	{
		exit(1);
	}
	return treebuild;
}
#endif

#ifndef POSTFIX_OFF
void makePostFix(TreeNode * t, FILE * fptr) {
	if (t == NULL)
	{
		return;
	}
	if (t->t.type == T_ADD || t->t.type == T_SUB || t->t.type == T_MUL || t->t.type == T_DIV)
	{
		makePostFix(t->left, fptr);
		makePostFix(t->right, fptr);
		fprintf(fptr, "%c ", t->t.type);
		return;
	}
	if (t->t.type == T_VAL)
	{
		fprintf(fptr, "%f ", t->t.value);
		return;	
	}
}
#endif
