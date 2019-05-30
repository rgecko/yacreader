#include "goto_dialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIntValidator>

GoToDialog::GoToDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
}

void GoToDialog::setupUI()
{
    textLabel = new QLabel(tr("Page : "));
    pageNumber = new QLineEdit;
    v = new QIntValidator(this);
    v->setBottom(1);
    pageNumber->setValidator(v);
    textLabel->setBuddy(pageNumber);
    textLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    accept = new QPushButton(tr("Go To"));
    connect(accept, SIGNAL(clicked()), this, SLOT(goTo()));
    cancel = new QPushButton(tr("Cancel"));
    connect(cancel, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *topLayout = new QHBoxLayout;

    topLayout->addWidget(textLabel);
    topLayout->addWidget(pageNumber);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    bottomLayout->addWidget(accept);
    bottomLayout->addWidget(cancel);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(numPagesLabel = new QLabel(tr("Total pages : ")));
    mainLayout->addLayout(topLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(bottomLayout);

    QHBoxLayout *imgMainLayout = new QHBoxLayout;
    QLabel *imgLabel = new QLabel();
    QPixmap p(":/images/goto.png");
    imgLabel->setPixmap(p);
    imgMainLayout->addWidget(imgLabel);
    imgMainLayout->addLayout(mainLayout);

    setLayout(imgMainLayout);

    setWindowTitle(tr("Go to..."));
    setModal(true);

    pageNumber->setFocusPolicy(Qt::StrongFocus);
    pageNumber->setFocus();
}

void GoToDialog::goTo()
{
    unsigned int page = pageNumber->text().toInt();
    pageNumber->clear();

    if (page >= 1)
        emit(goToPage(page - 1));

    close();
}

void GoToDialog::setNumPages(unsigned int numPages)
{
    numPagesLabel->setText(tr("Total pages : ") + QString::number(numPages));
    v->setTop(numPages);
}

void GoToDialog::open()
{
    pageNumber->setFocus();
    QDialog::open();
}
