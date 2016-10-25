/*
-----------------------------------------------------------------------------
CSCI356: Game Engine Essentials - Assignment 3

Name: Ivana Ozakovic
Student No.: 4790339
Email: io447@uow.edu.au

Filename:   SelectionBox.h
			The code used in this source file is part of Ogre Tutorials and has been modified for the purpose of this assignment.
			
-----------------------------------------------------------------------------
*/
#ifndef SELECTIONBOX_H
#define SELECTIONBOX_H
 
#include <OgreManualObject.h>
 
class SelectionBox : public Ogre::ManualObject
{
public:
  SelectionBox(const Ogre::String& name);
  virtual ~SelectionBox();
 
  void setCorners(float left, float top, float right, float bottom);
  void setCorners(const Ogre::Vector2& topLeft, const Ogre::Vector2& bottomRight);
};
 
 
#endif /* SELECTIONBOX_H */