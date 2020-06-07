using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;

namespace AnimalLibrary
{
    public class AnimalFactory
    {
        public static Animal CreateAnimal(string animalCategory, string animalName,int shoutNumber)
        {
            Animal result=null;
            object[] obj=new object[1];
            obj[0]=animalName;
            result = (Animal)Assembly.Load("AnimalLibrary").CreateInstance("AnimalLibrary."+animalCategory, false, BindingFlags.CreateInstance, null, obj, null, null);
            result.ShoutNum = shoutNumber;
            return result;
        }
    }
}
