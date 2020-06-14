-- $Id: dbc_concrete.e,v 1.6 1999/08/01 16:25:31 andy Exp $

indexing
   description: "Dummy class that instantiates DBC";

class
   DBC_CONCRETE

inherit 
   DBC
   end;

creation

   make

feature -- Initialization --------------------------------------------

   make is
   do
      my_first := Void
      my_last := Void
   end;

feature -- Commands --------------------------------------------------
   add_item (item : STRING) : NODE is
   local
      n : NODE
      temp : NODE
   do
      !!n.make(item)
      result := n
      if (my_first = Void) 
      then
        my_first := n
        my_last := n
        n.set_next(n)
        n.set_previous(n)
      else
         temp := my_last.previous
         temp.set_next(n)
         my_last.set_previous(n)
         n.set_next(my_last)
         n.set_previous(temp)
		end
   end

   find_item (item : STRING) : NODE is 
   local
      n : NODE
      done : BOOLEAN
   do
      from 
         n := my_first; done := false
      until 
         done
      loop
         if (n.value.compare (item) = 0) 
         then
            result := n
            done := true
         end
         if (n.next = my_last)
         then
           done := true
         end
         n := n.next
      end
   end

feature -- Queries ---------------------------------------------------

feature -- Properties ------------------------------------------------

feature {NONE} -- Privates -------------------------------------------
   my_first : NODE
   my_last : NODE

end -- class DBC_CONCRETE

-- Emacs Editing ------
-- Local Variables: 
-- tab-width:3
-- viper-shift-width:3
-- viper-auto-indent:t
-- End:
