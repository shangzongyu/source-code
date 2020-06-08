#include "find_dialog.h"

FindDialog::FindDialog(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{	
	label	 = new QLabel(tr("Find &what:"));
    lineEdit = new QLineEdit;	
    label->setBuddy(lineEdit);

    caseCheckBox     = new QCheckBox(tr("Match &case"));
    backwardCheckBox = new QCheckBox(tr("Search &backward"));
    findButton		 = new QPushButton(tr("&Find"));
    closeButton		 = new QPushButton(tr("Close"));
	findButton->setDefault(true);
    findButton->setEnabled(false);

	connect(lineEdit, SIGNAL(textChanged(const QString &)),
			this, SLOT(enableFindButton(const QString &))	);
	connect(findButton, SIGNAL(clicked()),
			this, SLOT(findClicked()));
	connect(closeButton, SIGNAL(clicked()),
			this, SLOT(close())	);
		
    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(caseCheckBox);
    leftLayout->addWidget(backwardCheckBox);
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(closeButton);
    
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);
	

    setWindowTitle(tr("Find"));
    setFixedHeight( sizeHint().height() );
}

void FindDialog::enableFindButton(const QString &text)
{
    findButton->setEnabled(!text.isEmpty());
}

void FindDialog::findClicked()
{
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs =
            caseCheckBox->isChecked() ? Qt::CaseSensitive
                                      : Qt::CaseInsensitive;
    //......
}


FindDialog::~FindDialog()
{

}



