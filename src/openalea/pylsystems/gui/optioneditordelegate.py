from PyQt4.QtCore import *
from PyQt4.QtGui import *

class OptionEditorDelegate(QItemDelegate):
    """ 
    Tool class used in LsysWindow editor 
    It allows to choose a value from a combobox in a QTable
    """

    def createEditor(self, parent, option, index):
        """ Create the editor """
        editor = QComboBox(parent)
        option = index.model().itemFromIndex(index).option
        editor.addItems([option[i].name for i in xrange(len(option))])
        return editor
    
    def setEditorData(self, editor, index):
        """ Accessor """
        editor.setCurrentIndex (index.model().itemFromIndex(index).option.selection)

    def setModelData(self, editor, model, index):
        """ Accessor """
        value = editor.currentIndex()
        model.itemFromIndex(index).option.setSelection(value)
        model.itemFromIndex(index).setText(editor.currentText())
