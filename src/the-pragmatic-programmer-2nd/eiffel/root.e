-- $Id: root.e,v 1.5 1999/08/01 21:18:40 andy Exp $

indexing
   description: "DBC directory's root class";
   note: "Initial version automatically generated"

class
   ROOT

creation

   make

feature -- Initialization --------------------------------------------

   make is
   local
      d: DBC_CONCRETE;
      n: NODE;
      n1: NODE;
      n2: NODE;
      n3: NODE;
   do
      !!d.make;
      n1 := d.add_item("TestA")
      n2 := d.add_item("TestB")
      n3 := d.add_item("TestC")

      n := d.find_item("TestB")

      check
         find_self: n = n2
         find_okay: n /= d.find_item("TestA");
         n1.next = n2
         n2.next = n3
         n3.next = n1
         n3.previous = n2
         n2.previous = n1
         n1.previous = n3
      end
   	std_output.put_string ("Eiffel test passed.%N")
   end;

feature -- Commands --------------------------------------------------

feature -- Queries ---------------------------------------------------

feature -- Properties ------------------------------------------------

feature {NONE} -- Privates -------------------------------------------

end -- class ROOT

-- Emacs Editing ------
-- Local Variables: 
-- tab-width:3
-- viper-shift-width:3
-- viper-auto-indent:t
-- End:
