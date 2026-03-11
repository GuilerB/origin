#include "mainwindow.h"
#include <QGroupBox>
#include <QRadioButton>
#include <QComboBox>
#include <QPushButton>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , progressValue(0)
{
    // Create a central widget
    centralWidget = new QWidget(this);

    // Create vertical layout
    mainLayout = new QVBoxLayout(centralWidget);

    groupBox = new QGroupBox("Choose a study area");

    // Horizontal layout inside the group
    QHBoxLayout *groupBoxLayout = new QHBoxLayout(groupBox);

    radioButton1 = new QRadioButton("Painters");
    radioButton2 = new QRadioButton("Musicians");

    groupBoxLayout->addWidget(radioButton1);
    groupBoxLayout->addWidget(radioButton2);

    groupBox->setLayout(groupBoxLayout);

    // Combo list
    comboBox = new QComboBox();
    comboBox->addItem("Camille Corot");
    comboBox->addItem("Edu Manet");
    comboBox->addItem("Johann Sebastian Bach");
    comboBox->addItem("Bruce Dickinson");

    // Button
    toggleButton = new QPushButton("A step in study progress!");
    toggleButton->setCheckable(true);

    // Progress bar
    progressBar = new QProgressBar();
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);
    progressBar->setValue(0);

    // Adding all widgets into the main layout
    mainLayout->addWidget(groupBox);
    mainLayout->addWidget(comboBox);
    mainLayout->addWidget(toggleButton);
    mainLayout->addWidget(progressBar);

    // Adding streatchable area in the end
    mainLayout->addStretch();

    // Layout for the central widget
    centralWidget->setLayout(mainLayout);

    // Central widget as main window
    setCentralWidget(centralWidget);

    // connect a slot with a signal
    connect(toggleButton, &QPushButton::clicked, this, &MainWindow::onToggleButtonClicked);

    resize(350, 250);
    setWindowTitle("Choose and study");
}

void MainWindow::onToggleButtonClicked()
{
    progressValue += 10;

    if (progressValue > 100) {
        progressValue = 0;
    }

    progressBar->setValue(progressValue);
}
