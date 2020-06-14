-- $Id: node.e,v 1.4 1999/08/01 16:25:31 andy Exp $
-- Andrew Hunt, Toolshed Technologies Inc.  (andy@toolshed.com)
-- Copyright (c) 1999 Toolshed Technologies, Inc.. All Rights Reserved.
--

indexing
   description: "Dummy node class";
   note: "Initial version automatically generated"

class
   NODE

creation

   make

feature -- Initialization --------------------------------------------

   make (a_value: STRING) is
   do
      my_value := a_value
   end;

feature -- Commands --------------------------------------------------

   set_previous(n : NODE) is
   do
      my_prev := n
   end

   set_next(n : NODE) is
   do
      my_next := n
   end

feature -- Queries ---------------------------------------------------

   value : STRING is
      do
         result := my_value
      end

   next : NODE is 
      do
      result := my_next
      end

   previous : NODE is 
      do
      result := my_prev
      end

feature -- Properties ------------------------------------------------

feature {NONE} -- Privates -------------------------------------------
   my_value : STRING
   my_prev : NODE
   my_next : NODE

end -- class NODE

-- Emacs Editing ------
-- Local Variables: 
-- tab-width:3
-- viper-shift-width:3
-- viper-auto-indent:t
-- End:
