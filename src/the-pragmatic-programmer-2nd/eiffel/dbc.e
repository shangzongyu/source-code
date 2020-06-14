--
-- $Id: dbc.e,v 1.13 2000/10/09 20:19:38 dave Exp $
--

indexing
   description: "DBC Exercise";
   note: "This was compiled with SmallEiffel -0.79"

class
   DBC

feature -- Commands --------------------------------------------------

   -- START: ans
   -- Add a unique item to a doubly linked list,
   -- and return the newly created NODE.

   add_item (item : STRING) : NODE is
      require
         item /= Void                  -- '/=' is 'not equal'.
         find_item(item) = Void        -- Must be unique
      deferred                         -- Abstract base class.
      ensure
         result.next.previous = result -- Check the newly
         result.previous.next = result -- added node's links.
         find_item(item) = result      -- Should find it.
      end
    -- END: ans


feature -- Queries ---------------------------------------------------

   find_item (item : STRING) : NODE is 
      deferred
      end

-- Properties ------------------------------------------------

feature {NONE} -- Privates -------------------------------------------

end -- class DBC

-- Emacs Editing ------
-- Local Variables: 
-- tab-width:3
-- viper-shift-width:3
-- viper-auto-indent:t
-- End:
