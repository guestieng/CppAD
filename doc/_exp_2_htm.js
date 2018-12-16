var list_across0 = [
'_contents.htm',
'_reference.htm',
'_index.htm',
'_search.htm',
'_external.htm'
];
var list_up0 = [
'cppad.htm',
'theory.htm',
'introduction.htm',
'exp_2.htm'
];
var list_down3 = [
'install.htm',
'theory.htm',
'ad.htm',
'adfun.htm',
'preprocessor.htm',
'multi_thread.htm',
'utility.htm',
'ipopt_solve.htm',
'example.htm',
'speed.htm',
'appendix.htm'
];
var list_down2 = [
'introduction.htm',
'forwardtheory.htm',
'reversetheory.htm',
'reverse_identity.htm',
'taylor_ode.htm',
'research.htm'
];
var list_down1 = [
'exp_2.htm',
'exp_eps.htm',
'exp_apx.cpp.htm'
];
var list_down0 = [
'exp_2.hpp.htm',
'exp_2.cpp.htm',
'exp_2_for0.htm',
'exp_2_for1.htm',
'exp_2_rev1.htm',
'exp_2_for2.htm',
'exp_2_rev2.htm',
'exp_2_cppad.htm'
];
var list_current0 = [
'exp_2.htm#Syntax',
'exp_2.htm#Purpose',
'exp_2.htm#Mathematical Form',
'exp_2.htm#include',
'exp_2.htm#x',
'exp_2.htm#y',
'exp_2.htm#Type',
'exp_2.htm#Contents',
'exp_2.htm#Implementation',
'exp_2.htm#Test',
'exp_2.htm#Exercises'
];
function choose_across0(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_across0[index-1];
}
function choose_up0(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_up0[index-1];
}
function choose_down3(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_down3[index-1];
}
function choose_down2(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_down2[index-1];
}
function choose_down1(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_down1[index-1];
}
function choose_down0(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_down0[index-1];
}
function choose_current0(item)
{	var index          = item.selectedIndex;
	item.selectedIndex = 0;
	if(index > 0)
		document.location = list_current0[index-1];
}