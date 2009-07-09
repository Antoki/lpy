/* ---------------------------------------------------------------------------
 #
 #       L-Py: L-systems in Python
 #
 #       Copyright 2003-2008 UMR Cirad/Inria/Inra Dap - Virtual Plant Team
 #
 #       File author(s): F. Boudon (frederic.boudon@cirad.fr)
 #
 # ---------------------------------------------------------------------------
 #
 #                      GNU General Public Licence
 #
 #       This program is free software; you can redistribute it and/or
 #       modify it under the terms of the GNU General Public License as
 #       published by the Free Software Foundation; either version 2 of
 #       the License, or (at your option) any later version.
 #
 #       This program is distributed in the hope that it will be useful,
 #       but WITHOUT ANY WARRANTY; without even the implied warranty of
 #       MERCHANTABILITY or FITNESS For A PARTICULAR PURPOSE. See the
 #       GNU General Public License for more details.
 #
 #       You should have received a copy of the GNU General Public
 #       License along with this program; see the file COPYING. If not,
 #       write to the Free Software Foundation, Inc., 59
 #       Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 #
 # ---------------------------------------------------------------------------
 */

#include "abstractlstring.h"
#include <plantgl/python/export_list.h>


template<class LString>
LString py_lstring_mult(const LString& lstring, int i) {
	LString res(lstring);
	res.mult(i);
	return res;
}

template<class LString>
LString& py_lstring_imult(LString* lstring, int i) {
	lstring->mult(i);
	return *lstring;
}


template<class LString>
int iter_to_int(LString * tree, typename LString::const_iterator pos)
{ 
  if (pos == tree->end()) return -1;
  else return tree->pos(pos);
}

template<class LString>
boost::python::object veciter_to_list(LString * tree, std::vector<typename LString::const_iterator> res)
{
  if (res.empty()) return boost::python::object(-1);
  else if (res.size() == 1) 
	return boost::python::object(tree->pos(res[0]));
  else {
	boost::python::list l;
	for(std::vector<typename LString::const_iterator>::const_iterator _it = res.begin();
		_it != res.end(); _it++)
		  l.append(tree->pos(*_it));
	return l;
  }
}


template<class LString>
typename LString::const_iterator int_to_iter(LString * tree, int pos)
{ 
  size_t len= tree->size();
  if(pos < 0)pos += len;
  typename LString::const_iterator beg = tree->begin();
  if(pos > 0 && pos <= len)beg += pos;
  else if(pos != 0){
	PyErr_SetString(PyExc_IndexError, "index out of range");
    throw_error_already_set();
  }
  return beg;
}


template<class LString>
boost::python::object py_roots(LString * tree)
{ return veciter_to_list(tree,tree->roots()); }

template<class LString>
int py_father(LString * tree, int pos)
{ return iter_to_int(tree,tree->father(int_to_iter(tree,pos))); }

template<class LString>
boost::python::object py_sons(LString * tree, int pos)
{ return veciter_to_list(tree,tree->sons(int_to_iter(tree,pos))); }

template<class LString>
boost::python::object py_lateralSons(LString * tree, int pos)
{ return veciter_to_list(tree,tree->lateralSons(int_to_iter(tree,pos))); }

template<class LString>
int py_directSon(LString * tree, int pos)
{ return iter_to_int(tree,tree->directSon(int_to_iter(tree,pos))); }

template<class LString>
int py_endBracket(LString * tree, int pos, bool startingBeforePos) 
{ return iter_to_int(tree,tree->endBracket(int_to_iter(tree,pos),startingBeforePos)); }

template<class LString>
int py_beginBracket(LString * tree, int pos, bool startingAfterPos) 
{ return iter_to_int(tree,tree->beginBracket(int_to_iter(tree,pos),startingAfterPos)); }

template<class LString>
int py_complex1(LString * tree, int pos, int scale)
{ return iter_to_int(tree,tree->complex(int_to_iter(tree,pos),scale)); }

template<class LString>
int py_complex(LString * tree, int pos)
{ return iter_to_int(tree,tree->complex(int_to_iter(tree,pos))); }

template<class LString>
int py_successor_at_scale(LString * tree, int pos, int scale)
{ return iter_to_int(tree,successor_at_scale(int_to_iter(tree,pos),scale,tree->const_end())); }

template<class LString>
int py_successor_at_level(LString * tree, int pos, int scale)
{ return iter_to_int(tree,successor_at_level(int_to_iter(tree,pos),scale,tree->const_end())); }

template<class LString>
int py_predecessor_at_scale(LString * tree, int pos, int scale)
{ return iter_to_int(tree,predecessor_at_scale(int_to_iter(tree,pos),scale,tree->const_begin(),tree->const_end())); }

template<class LString>
int py_predecessor_at_level(LString * tree, int pos, int scale)
{ return iter_to_int(tree,predecessor_at_level(int_to_iter(tree,pos),scale,tree->const_begin(),tree->const_end())); }

template<class LString>
LString& py_iadd_lstring(LString * first, const LString& pattern) 
{ first->append(pattern);  return *first; }

template<class LString>
LString& py_iadd_lstring_mod(LString * first, const typename LString::ModuleType& pattern) 
{ first->append(pattern);  return *first; }

template<class LString>
LString py_add_lstring_mod(LString * first, const typename LString::ModuleType& pattern) 
{  LString res(*first); res.append(pattern);  return res; }

template<class LString>
LString py_add_lstring(LString * first, const LString& pattern) 
{  LString res(*first); res.append(pattern);  return res; }

template<class LString>
void py_append_lstring(LString * first, const std::string& pattern) { first->append(LString(pattern)); }

template<class LString>
void py_prepend_lstring(LString * first, const std::string& pattern) { first->prepend(LString(pattern)); }

template<class LString>
void py_insert_lstring(LString * first, int i, const std::string& pattern) { first->insertItemAt(i,LString(pattern)); }

template<class LString>
class lstring_func : public boost::python::def_visitor<lstring_func<LString> >
{
	typedef typename LString::ModuleType Module;

    friend class boost::python::def_visitor_access;

    template <class classT>
    void visit(classT& c) const
	{
		c.def("argSize", &LString::size)
		 .def("empty",  &LString::empty)
		 .def("clear",  &LString::clear)
		 .def("__len__", &LString::size)
		 .def("__getitem__",&LString::getItemAt)
		 .def("__setitem__",&LString::setItemAt)
		 .def("__delitem__",&LString::removeItemAt)
		 .def("__getslice__",&LString::getRange<LString>)
		 .def("__delslice__",&LString::removeRange)
		 .def("append",(void(LString::*)(const Module&))&LString::append)
		 .def("append",&LString::append<LString>)
		 .def("append",&py_append_lstring<LString>)
		 .def("__iadd__",&py_iadd_lstring<LString>, return_internal_reference<1>())
		 .def("__iadd__",&py_iadd_lstring_mod<LString>, return_internal_reference<1>())
		 .def("__add__",&py_add_lstring<LString>)
		 .def("__add__",&py_add_lstring_mod<LString>)
		 .def("prepend",(void(LString::*)(const Module&))&LString::prepend)
		 .def("prepend",&LString::prepend<LString>)
		 .def("prepend",&py_prepend_lstring<LString>)
		 .def("insertAt",(void(LString::*)(int,const Module&))&LString::insertItemAt)
		 .def("insertAt",&LString::insertItemAt<LString>)
		 .def("insertAt",&py_insert_lstring<LString>)
		 .def("__mul__",&py_lstring_mult<LString>)
		 .def("__imul__",&py_lstring_imult<LString>, return_internal_reference<1>())

		 .def(self == self)
		 .def(self != self)

		 .def( "wellBracketed", &LString::wellBracketed )
		 .def( "isAPath", &LString::isAPath )
		 .def( "hasRequestModule", &LString::hasRequestModule )

		 .def( "roots",  &py_roots<LString> ) 
		 .def( "father", &py_father<LString>, args("pos") ) 
		 .def( "sons",   &py_sons<LString>, args("pos") ) 
		 .def( "lateralSons", &py_lateralSons<LString>, args("pos") ) 
		 .def( "directSon", &py_directSon<LString>, args("pos") ) 
		 .def( "endBracket", &py_endBracket<LString>, (bp::arg("startingBeforePos")=false) ) 
		 .def( "beginBracket", &py_beginBracket<LString>, (bp::arg("startingAfterPos")=false) ) 
		 .def( "complex", &py_complex1<LString>, args("pos") ) 
		 .def( "complex", &py_complex<LString>, args("pos","scale") ) 
		 .def( "successor_at_scale", &py_successor_at_scale<LString>, args("pos","scale") ) 
		 .def( "successor_at_level", &py_successor_at_level<LString>, args("pos","level") ) 
		 .def( "predecessor_at_scale", &py_predecessor_at_scale<LString>, args("pos","scale") ) 
		 .def( "predecessor_at_level", &py_predecessor_at_level<LString>, args("pos","level") ) 
		 ;
    }
};


