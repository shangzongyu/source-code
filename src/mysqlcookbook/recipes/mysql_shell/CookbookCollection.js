var CookbookCollection = { 
  // Collection where the object is stored
  collection: null, 
  
  // Searches collection and returns first
  // object that satisfy search condition.
  find: function(searchCondition) { 
    return this.collection.find(searchCondition).
             execute().fetchOne(); 
  },
  
  // Saves the object in the database
  save: function() {
    // If we know _id of the object we are updating existing one
    // We use not so effective method addOrReplaceOne instead of modify
    // for simplicity.
    if ('_id' in this) {
      this.collection.addOrReplaceOne(this._id,
        // We use  double conversion, because we cannot store
        // object with methods in the database
        JSON.parse(
          JSON.stringify(
            this, Object.getOwnPropertyNames(
                    Object.getPrototypeOf(this))
          )
        )
      )
    } else {
      // In case if the object does not exist in the database yet
      // we add it and assign generated _id to own property.
      // This _id could be used later if we want to update
      // or remove the database entry.
      this._id = this.collection.add(
        JSON.parse(
          JSON.stringify(
            this, Object.getOwnPropertyNames(
                    Object.getPrototypeOf(this))
          )
        )
      ).execute().getGeneratedIds()[0]
    }
  },
  
  // Removes the entry from the database.
  // Once removed we unset property _id of the object.
  remove: function() {
    this.collection.remove("_id = '" + this._id + "'").execute()
    delete Object.getPrototypeOf(this)._id
    delete this._id
  }
}
