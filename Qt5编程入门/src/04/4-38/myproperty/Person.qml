import QtQuick 2.2

Displayable {
    property string title
    property string firstName
    property string lastName

    function fullName()  { return title + " " + firstName + " " + lastName }
}
