var list_across0 = [
'_contents.htm',
'_reference.htm',
'_index.htm',
'_search.htm',
'_external.htm'
];
var list_up0 = [
'cppad.htm',
'appendix.htm',
'deprecated.htm',
'atomic_two.htm',
'atomic_two_for_sparse_hes.htm'
];
var list_current0 = [
'atomic_two_for_sparse_hes.htm#Syntax',
'atomic_two_for_sparse_hes.htm#Deprecated 2016-06-27',
'atomic_two_for_sparse_hes.htm#Purpose',
'atomic_two_for_sparse_hes.htm#Implementation',
'atomic_two_for_sparse_hes.htm#Implementation.vx',
'atomic_two_for_sparse_hes.htm#Implementation.r',
'atomic_two_for_sparse_hes.htm#Implementation.s',
'atomic_two_for_sparse_hes.htm#Implementation.h',
'atomic_two_for_sparse_hes.htm#Implementation.x'
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