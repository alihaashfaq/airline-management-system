#include "mainwindow.h"
#include "ticket.h"
#include "payment.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

// ============================================================
//  STYLE
// ============================================================
void MainWindow::applyStyle() {
    setStyleSheet(R"(
QMainWindow, QWidget {
    background: transparent;
    color: #e8f4fd;
    font-family: "Segoe UI";
    font-size: 13px;
}
QLabel { color: #cce4f6; padding: 2px; background: transparent; }

QLineEdit {
    background-color: rgba(10, 30, 60, 210);
    color: #e8f4fd;
    border: 1.5px solid #1e4976;
    border-radius: 8px;
    padding: 9px 13px;
    font-size: 13px;
}
QLineEdit:focus {
    border: 2px solid #00d4ff;
    background-color: rgba(13, 42, 74, 230);
}

QComboBox {
    background-color: rgba(10, 30, 60, 210);
    color: #e8f4fd;
    border: 1.5px solid #1e4976;
    border-radius: 8px;
    padding: 9px 13px;
    font-size: 13px;
}
QComboBox:focus { border: 2px solid #00d4ff; }
QComboBox::drop-down {
    border: none;
    width: 24px;
}
QComboBox QAbstractItemView {
    background-color: #0d2044;
    color: #e8f4fd;
    selection-background-color: #1e4976;
    border: 1px solid #1e4976;
    padding: 4px;
}

QPushButton {
    background: qlineargradient(x1:0,y1:0,x2:1,y2:0,
        stop:0 #1e4976, stop:1 #00b4d8);
    color: white;
    border: none;
    border-radius: 8px;
    padding: 10px 22px;
    font-weight: bold;
    font-size: 13px;
    min-height: 38px;
}
QPushButton:hover {
    background: qlineargradient(x1:0,y1:0,x2:1,y2:0,
        stop:0 #00b4d8, stop:1 #0096c7);
}
QPushButton:pressed { background: #023e8a; }

QTextEdit {
    background-color: rgba(4, 12, 28, 220);
    color: #00ff88;
    border: 1.5px solid #1e4976;
    border-radius: 10px;
    padding: 12px;
    font-family: "Courier New";
    font-size: 12px;
}

QGroupBox {
    background-color: rgba(8, 22, 50, 185);
    border: 1.5px solid #1e4976;
    border-radius: 12px;
    margin-top: 14px;
    padding: 16px;
    font-weight: bold;
    color: #00d4ff;
    font-size: 13px;
}
QGroupBox::title {
    subcontrol-origin: margin;
    left: 16px;
    padding: 0 10px;
    color: #00d4ff;
}

QScrollBar:vertical {
    background: rgba(4,12,28,180);
    width: 8px;
    border-radius: 4px;
}
QScrollBar::handle:vertical {
    background: #1e4976;
    border-radius: 4px;
    min-height: 30px;
}
QScrollBar::handle:vertical:hover { background: #00d4ff; }
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; }
    )");
}

// ============================================================
//  PAINT EVENT
// ============================================================
void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (!bgImage.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), bgImage);
        painter.fillRect(rect(), QColor(6, 15, 32, 162));
    } else {
        painter.fillRect(rect(), QColor(10, 22, 40));
    }
    QMainWindow::paintEvent(event);
}

// ============================================================
//  HELPERS
// ============================================================
QLabel* MainWindow::makeLabel(const QString &text) {
    QLabel *l = new QLabel(text);
    l->setStyleSheet("background:transparent; color:#aed6f1;");
    return l;
}

QPushButton* MainWindow::menuCard(const QString &icon,
                                  const QString &title,
                                  const QString &desc,
                                  const QString &color) {
    QPushButton *btn = new QPushButton();
    btn->setFixedHeight(88);
    btn->setText(icon + "   " + title + "\n        " + desc);
    btn->setStyleSheet(QString(
                           "QPushButton {"
                           "  background: qlineargradient(x1:0,y1:0,x2:1,y2:1,"
                           "    stop:0 rgba(%1,35), stop:1 rgba(%1,75));"
                           "  border: 1.5px solid rgba(%1,110);"
                           "  border-radius: 12px;"
                           "  color: white;"
                           "  font-size: 14px;"
                           "  font-weight: bold;"
                           "  text-align: left;"
                           "  padding: 14px 22px;"
                           "}"
                           "QPushButton:hover {"
                           "  background: qlineargradient(x1:0,y1:0,x2:1,y2:1,"
                           "    stop:0 rgba(%1,80), stop:1 rgba(%1,130));"
                           "  border: 1.5px solid rgba(%1,200);"
                           "}"
                           "QPushButton:pressed { background: rgba(%1,130); }"
                           ).arg(color));
    return btn;
}

void MainWindow::showDataPage(const QString &title, const QString &content) {
    lblDataTitle->setText(title);
    txtDataOutput->setPlainText(content);
    stackedWidget->setCurrentIndex(PAGE_DATA_VIEW);
}

// ============================================================
//  PAGE 0 — LOGIN
// ============================================================
QWidget* MainWindow::buildLoginPage() {
    QWidget *page = new QWidget;
    page->setAttribute(Qt::WA_TranslucentBackground);
    QVBoxLayout *lay = new QVBoxLayout(page);
    lay->setContentsMargins(140, 50, 140, 50);
    lay->setSpacing(16);

    QLabel *banner = new QLabel("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
    banner->setAlignment(Qt::AlignCenter);
    banner->setStyleSheet("color:#1a3a6b; font-size:15px; background:transparent;");
    lay->addWidget(banner);

    QLabel *title = new QLabel("SKYLINE AIRLINES");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size:30px; font-weight:900; color:#00d4ff;"
        "letter-spacing:5px; background:transparent;");
    lay->addWidget(title);

    QLabel *sub = new QLabel("Your Journey Begins Here");
    sub->setAlignment(Qt::AlignCenter);
    sub->setStyleSheet("color:#5ba3c9; font-size:13px; background:transparent;");
    lay->addWidget(sub);

    QLabel *div = new QLabel("________________________________________________");
    div->setAlignment(Qt::AlignCenter);
    div->setStyleSheet("color:#1a3a6b; background:transparent;");
    lay->addWidget(div);

    QGroupBox *box = new QGroupBox("  Secure Login");
    QVBoxLayout *bl = new QVBoxLayout(box);
    bl->setSpacing(12);
    bl->addWidget(makeLabel("Username"));
    txtUsername = new QLineEdit;
    txtUsername->setPlaceholderText("Enter username...");
    bl->addWidget(txtUsername);
    bl->addWidget(makeLabel("Password"));
    txtPassword = new QLineEdit;
    txtPassword->setPlaceholderText("Enter password...");
    txtPassword->setEchoMode(QLineEdit::Password);
    bl->addWidget(txtPassword);
    lay->addWidget(box);
    lay->addStretch();

    QHBoxLayout *br = new QHBoxLayout;
    br->setSpacing(16);

    QPushButton *bAdmin = new QPushButton("Admin Login");
    bAdmin->setFixedHeight(46);
    bAdmin->setStyleSheet(
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,"
        "stop:0 #1a3a6b,stop:1 #2196F3);"
        "color:white; border:none; border-radius:10px;"
        "font-size:14px; font-weight:bold; min-height:46px;");

    QPushButton *bPass = new QPushButton("Passenger Login");
    bPass->setFixedHeight(46);
    bPass->setStyleSheet(
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,"
        "stop:0 #0d4a2e,stop:1 #00c853);"
        "color:white; border:none; border-radius:10px;"
        "font-size:14px; font-weight:bold; min-height:46px;");

    connect(bAdmin, &QPushButton::clicked, this, &MainWindow::on_btnAdminLogin_clicked);
    connect(bPass,  &QPushButton::clicked, this, &MainWindow::on_btnPassengerLogin_clicked);
    br->addWidget(bAdmin);
    br->addWidget(bPass);
    lay->addLayout(br);

    QLabel *hint = new QLabel("Admin:  username = admin  |  password = 1234");
    hint->setAlignment(Qt::AlignCenter);
    hint->setStyleSheet("color:#2a5070; font-size:11px; background:transparent;");
    lay->addWidget(hint);

    return page;
}

// ============================================================
//  PAGE 1 — ADMIN MENU
// ============================================================
QWidget* MainWindow::buildAdminMenuPage() {
    QWidget *page = new QWidget;
    page->setAttribute(Qt::WA_TranslucentBackground);
    QVBoxLayout *lay = new QVBoxLayout(page);
    lay->setContentsMargins(30, 20, 30, 20);
    lay->setSpacing(12);

    QLabel *hdr = new QLabel("ADMIN PANEL  |  SkyLine Airlines");
    hdr->setAlignment(Qt::AlignCenter);
    hdr->setStyleSheet(
        "font-size:20px; font-weight:900; color:#00d4ff;"
        "background:rgba(4,14,36,200); border-radius:10px;"
        "padding:12px; letter-spacing:2px;");
    lay->addWidget(hdr);

    QLabel *sub = new QLabel("Select an option to manage your airline");
    sub->setAlignment(Qt::AlignCenter);
    sub->setStyleSheet("color:#5ba3c9; font-size:12px; background:transparent;");
    lay->addWidget(sub);

    QHBoxLayout *row1 = new QHBoxLayout; row1->setSpacing(12);
    QPushButton *cAdd  = menuCard("[+]", "Add Flight",      "Register a new flight route",  "30,100,180");
    QPushButton *cShow = menuCard("[=]", "Show Flights",    "View all available flights",   "0,140,180");
    QPushButton *cTot  = menuCard("[#]", "Total Flights",   "Count of registered flights",  "0,100,160");
    row1->addWidget(cAdd); row1->addWidget(cShow); row1->addWidget(cTot);
    lay->addLayout(row1);

    QHBoxLayout *row2 = new QHBoxLayout; row2->setSpacing(12);
    QPushButton *cConf = menuCard("[*]", "Confidential",    "Secure flight seat data",      "120,50,160");
    QPushButton *cPass = menuCard("[@]", "Passengers",      "All passenger records",        "0,120,100");
    QPushButton *cRev  = menuCard("[$]", "Revenue",         "Total earnings summary",       "180,120,0");
    row2->addWidget(cConf); row2->addWidget(cPass); row2->addWidget(cRev);
    lay->addLayout(row2);

    QHBoxLayout *row3 = new QHBoxLayout; row3->setSpacing(12);
    QPushButton *cSeat = menuCard("[S]", "Seat Allocation", "Flight-wise seat map",         "0,80,140");
    row3->addWidget(cSeat);
    row3->addStretch();
    row3->addStretch();
    lay->addLayout(row3);

    lay->addStretch();

    QPushButton *bBack = new QPushButton("Logout");
    bBack->setFixedHeight(42);
    bBack->setStyleSheet(
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,"
        "stop:0 #3a0a0a,stop:1 #c62828);"
        "color:white; border:none; border-radius:8px;"
        "font-size:13px; font-weight:bold;");
    lay->addWidget(bBack);

    connect(cAdd,  &QPushButton::clicked, this, &MainWindow::on_adminMenu_AddFlight_clicked);
    connect(cShow, &QPushButton::clicked, this, &MainWindow::on_adminMenu_ShowFlights_clicked);
    connect(cTot,  &QPushButton::clicked, this, &MainWindow::on_adminMenu_TotalFlights_clicked);
    connect(cConf, &QPushButton::clicked, this, &MainWindow::on_adminMenu_Confidential_clicked);
    connect(cPass, &QPushButton::clicked, this, &MainWindow::on_adminMenu_Passengers_clicked);
    connect(cRev,  &QPushButton::clicked, this, &MainWindow::on_adminMenu_Revenue_clicked);
    connect(cSeat, &QPushButton::clicked, this, &MainWindow::on_adminMenu_SeatAlloc_clicked);
    connect(bBack, &QPushButton::clicked, this, &MainWindow::on_adminMenu_Back_clicked);

    return page;
}

// ============================================================
//  PAGE 2 — ADD FLIGHT
// ============================================================
QWidget* MainWindow::buildAddFlightPage() {
    QWidget *page = new QWidget;
    page->setAttribute(Qt::WA_TranslucentBackground);
    QVBoxLayout *lay = new QVBoxLayout(page);
    lay->setContentsMargins(60, 25, 60, 25);
    lay->setSpacing(14);

    QLabel *hdr = new QLabel("[+]  ADD NEW FLIGHT");
    hdr->setAlignment(Qt::AlignCenter);
    hdr->setStyleSheet(
        "font-size:18px; font-weight:900; color:#00d4ff;"
        "background:rgba(4,14,36,200); border-radius:10px; padding:12px;");
    lay->addWidget(hdr);

    QGroupBox *form = new QGroupBox("  Flight Details");
    QGridLayout *gl = new QGridLayout(form);
    gl->setSpacing(12);
    gl->setColumnStretch(1, 1);
    gl->setColumnStretch(3, 1);

    txtFlightNo    = new QLineEdit; txtFlightNo->setPlaceholderText("e.g. PK-301");
    txtAirline     = new QLineEdit; txtAirline->setPlaceholderText("e.g. PIA");
    txtDestination = new QLineEdit; txtDestination->setPlaceholderText("e.g. Dubai");
    txtDeparture   = new QLineEdit; txtDeparture->setPlaceholderText("e.g. 10:00 AM");
    txtArrival     = new QLineEdit; txtArrival->setPlaceholderText("e.g. 02:00 PM");
    txtSeats       = new QLineEdit; txtSeats->setPlaceholderText("e.g. 150");

    gl->addWidget(makeLabel("Flight No :"),   0,0); gl->addWidget(txtFlightNo,    0,1);
    gl->addWidget(makeLabel("Airline :"),     0,2); gl->addWidget(txtAirline,     0,3);
    gl->addWidget(makeLabel("Destination :"), 1,0); gl->addWidget(txtDestination, 1,1);
    gl->addWidget(makeLabel("Departure :"),   1,2); gl->addWidget(txtDeparture,   1,3);
    gl->addWidget(makeLabel("Arrival :"),     2,0); gl->addWidget(txtArrival,     2,1);
    gl->addWidget(makeLabel("Total Seats :"), 2,2); gl->addWidget(txtSeats,       2,3);
    lay->addWidget(form);
    lay->addStretch();

    QHBoxLayout *br = new QHBoxLayout; br->setSpacing(14);

    QPushButton *bAdd = new QPushButton("Add Flight");
    bAdd->setFixedHeight(46);
    bAdd->setStyleSheet(
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,"
        "stop:0 #1a3a6b,stop:1 #2196F3);"
        "color:white; border:none; border-radius:10px;"
        "font-size:14px; font-weight:bold;");

    QPushButton *bBack = new QPushButton("Back to Menu");
    bBack->setFixedHeight(46);
    bBack->setStyleSheet(
        "QPushButton { background:rgba(20,40,70,200); color:#7ab8d4;"
        "border:1.5px solid #1e4976; border-radius:10px;"
        "font-size:13px; font-weight:bold; }"
        "QPushButton:hover { background:rgba(30,73,118,200); color:white; }");

    connect(bAdd,  &QPushButton::clicked, this, &MainWindow::on_btnAddFlight_clicked);
    connect(bBack, &QPushButton::clicked, this, &MainWindow::on_btnAddFlight_Back_clicked);
    br->addWidget(bAdd);
    br->addWidget(bBack);
    lay->addLayout(br);

    return page;
}

// ============================================================
//  PAGE 3 — DATA VIEW
// ============================================================
QWidget* MainWindow::buildDataViewPage() {
    QWidget *page = new QWidget;
    page->setAttribute(Qt::WA_TranslucentBackground);
    QVBoxLayout *lay = new QVBoxLayout(page);
    lay->setContentsMargins(40, 20, 40, 20);
    lay->setSpacing(14);

    lblDataTitle = new QLabel("Data");
    lblDataTitle->setAlignment(Qt::AlignCenter);
    lblDataTitle->setStyleSheet(
        "font-size:18px; font-weight:900; color:#00d4ff;"
        "background:rgba(4,14,36,200); border-radius:10px; padding:12px;");
    lay->addWidget(lblDataTitle);

    QGroupBox *og = new QGroupBox("  Result");
    QVBoxLayout *ol = new QVBoxLayout(og);
    txtDataOutput = new QTextEdit;
    txtDataOutput->setReadOnly(true);
    txtDataOutput->setMinimumHeight(360);
    ol->addWidget(txtDataOutput);
    lay->addWidget(og);

    QPushButton *bBack = new QPushButton("Back to Admin Menu");
    bBack->setFixedHeight(44);
    bBack->setStyleSheet(
        "QPushButton { background:rgba(20,40,70,200); color:#7ab8d4;"
        "border:1.5px solid #1e4976; border-radius:10px;"
        "font-size:13px; font-weight:bold; }"
        "QPushButton:hover { background:rgba(30,73,118,200); color:white; }");
    connect(bBack, &QPushButton::clicked, this, &MainWindow::on_btnDataView_Back_clicked);
    lay->addWidget(bBack);

    return page;
}

// ============================================================
//  PAGE 4 — PASSENGER MENU
// ============================================================
QWidget* MainWindow::buildPassMenuPage() {
    QWidget *page = new QWidget;
    page->setAttribute(Qt::WA_TranslucentBackground);
    QVBoxLayout *lay = new QVBoxLayout(page);
    lay->setContentsMargins(80, 30, 80, 30);
    lay->setSpacing(16);

    QLabel *hdr = new QLabel("PASSENGER PORTAL  |  SkyLine Airlines");
    hdr->setAlignment(Qt::AlignCenter);
    hdr->setStyleSheet(
        "font-size:20px; font-weight:900; color:#00ff88;"
        "background:rgba(4,14,36,200); border-radius:10px;"
        "padding:12px; letter-spacing:2px;");
    lay->addWidget(hdr);

    QLabel *sub = new QLabel("What would you like to do?");
    sub->setAlignment(Qt::AlignCenter);
    sub->setStyleSheet("color:#5ba3c9; font-size:12px; background:transparent;");
    lay->addWidget(sub);

    lay->addStretch();

    QPushButton *cBook   = menuCard("[>>]", "Book a Ticket",   "Reserve your seat on a flight",  "0,140,80");
    QPushButton *cView   = menuCard("[==]", "View My Tickets", "See all your bookings",          "0,100,160");
    QPushButton *cCancel = menuCard("[ X]", "Cancel a Ticket", "Remove an existing booking",     "160,40,40");
    cBook->setFixedHeight(100);
    cView->setFixedHeight(100);
    cCancel->setFixedHeight(100);

    lay->addWidget(cBook);
    lay->addWidget(cView);
    lay->addWidget(cCancel);
    lay->addStretch();

    QPushButton *bBack = new QPushButton("Logout");
    bBack->setFixedHeight(42);
    bBack->setStyleSheet(
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,"
        "stop:0 #3a0a0a,stop:1 #c62828);"
        "color:white; border:none; border-radius:8px;"
        "font-size:13px; font-weight:bold;");
    lay->addWidget(bBack);

    connect(cBook,   &QPushButton::clicked, this, &MainWindow::on_passMenu_Book_clicked);
    connect(cView,   &QPushButton::clicked, this, &MainWindow::on_passMenu_View_clicked);
    connect(cCancel, &QPushButton::clicked, this, &MainWindow::on_passMenu_Cancel_clicked);
    connect(bBack,   &QPushButton::clicked, this, &MainWindow::on_passMenu_Back_clicked);

    return page;
}

// ============================================================
//  PAGE 5 — BOOK TICKET
// ============================================================
QWidget* MainWindow::buildBookPage() {
    QWidget *page = new QWidget;
    page->setAttribute(Qt::WA_TranslucentBackground);
    QVBoxLayout *lay = new QVBoxLayout(page);
    lay->setContentsMargins(50, 20, 50, 20);
    lay->setSpacing(12);

    QLabel *hdr = new QLabel("[>>]  BOOK A TICKET");
    hdr->setAlignment(Qt::AlignCenter);
    hdr->setStyleSheet(
        "font-size:18px; font-weight:900; color:#00ff88;"
        "background:rgba(4,14,36,200); border-radius:10px; padding:12px;");
    lay->addWidget(hdr);

    QGroupBox *form = new QGroupBox("  Booking Details");
    QGridLayout *gl = new QGridLayout(form);
    gl->setSpacing(12);
    gl->setColumnStretch(1, 1);
    gl->setColumnStretch(3, 1);

    txtPassName = new QLineEdit;
    txtPassName->setPlaceholderText("Your full name");

    // Flight dropdown
    cmbFlights = new QComboBox;
    cmbFlights->addItem("-- Select a Flight --");
    cmbFlights->setStyleSheet(
        "QComboBox { background-color:rgba(10,30,60,220); color:#00d4ff;"
        "border:1.5px solid #00d4ff; border-radius:8px; padding:9px 13px;"
        "font-size:13px; font-weight:bold; }"
        "QComboBox:focus { border:2px solid #00ff88; }"
        "QComboBox QAbstractItemView { background-color:#0d2044; color:#e8f4fd;"
        "selection-background-color:#1e4976; border:1px solid #1e4976; padding:4px; }");

    txtPassSeat = new QLineEdit;
    txtPassSeat->setPlaceholderText("e.g. 12");

    cmbClass = new QComboBox;
    cmbClass->addItem("Economy  -  Rs. 500");
    cmbClass->addItem("Business  -  Rs. 1000");

    cmbPayment = new QComboBox;
    cmbPayment->addItem("Cash");
    cmbPayment->addItem("Card");

    gl->addWidget(makeLabel("Full Name :"),     0, 0); gl->addWidget(txtPassName, 0, 1);
    gl->addWidget(makeLabel("Select Flight :"), 0, 2); gl->addWidget(cmbFlights,  0, 3);
    gl->addWidget(makeLabel("Seat No :"),       1, 0); gl->addWidget(txtPassSeat, 1, 1);
    gl->addWidget(makeLabel("Class :"),         1, 2); gl->addWidget(cmbClass,    1, 3);
    gl->addWidget(makeLabel("Payment :"),       2, 0); gl->addWidget(cmbPayment,  2, 1);

    lay->addWidget(form);

    // Confirmation output
    QGroupBox *og = new QGroupBox("  Booking Confirmation");
    QVBoxLayout *ol = new QVBoxLayout(og);
    txtBookOutput = new QTextEdit;
    txtBookOutput->setReadOnly(true);
    txtBookOutput->setMinimumHeight(150);
    txtBookOutput->setPlaceholderText("Confirmation will appear here after booking...");
    ol->addWidget(txtBookOutput);
    lay->addWidget(og);

    QHBoxLayout *br = new QHBoxLayout; br->setSpacing(12);

    QPushButton *bBook = new QPushButton("Confirm Booking");
    bBook->setFixedHeight(46);
    bBook->setStyleSheet(
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,"
        "stop:0 #0d4a2e,stop:1 #00c853);"
        "color:white; border:none; border-radius:10px;"
        "font-size:14px; font-weight:bold;");

    QPushButton *bBack = new QPushButton("Back to Menu");
    bBack->setFixedHeight(46);
    bBack->setStyleSheet(
        "QPushButton { background:rgba(20,40,70,200); color:#7ab8d4;"
        "border:1.5px solid #1e4976; border-radius:10px;"
        "font-size:13px; font-weight:bold; }"
        "QPushButton:hover { background:rgba(30,73,118,200); color:white; }");

    connect(bBook, &QPushButton::clicked, this, &MainWindow::on_btnBookTicket_clicked);
    connect(bBack, &QPushButton::clicked, this, &MainWindow::on_btnBook_Back_clicked);
    br->addWidget(bBook);
    br->addWidget(bBack);
    lay->addLayout(br);

    return page;
}

// ============================================================
//  PAGE 6 — VIEW TICKETS
// ============================================================
QWidget* MainWindow::buildViewPage() {
    QWidget *page = new QWidget;
    page->setAttribute(Qt::WA_TranslucentBackground);
    QVBoxLayout *lay = new QVBoxLayout(page);
    lay->setContentsMargins(40, 20, 40, 20);
    lay->setSpacing(12);

    QLabel *hdr = new QLabel("[==]  MY TICKETS");
    hdr->setAlignment(Qt::AlignCenter);
    hdr->setStyleSheet(
        "font-size:18px; font-weight:900; color:#00d4ff;"
        "background:rgba(4,14,36,200); border-radius:10px; padding:12px;");
    lay->addWidget(hdr);

    QGroupBox *og = new QGroupBox("  All Booked Tickets");
    QVBoxLayout *ol = new QVBoxLayout(og);
    txtViewOutput = new QTextEdit;
    txtViewOutput->setReadOnly(true);
    txtViewOutput->setMinimumHeight(380);
    txtViewOutput->setPlaceholderText("No tickets found...");
    ol->addWidget(txtViewOutput);
    lay->addWidget(og);

    QPushButton *bBack = new QPushButton("Back to Menu");
    bBack->setFixedHeight(44);
    bBack->setStyleSheet(
        "QPushButton { background:rgba(20,40,70,200); color:#7ab8d4;"
        "border:1.5px solid #1e4976; border-radius:10px;"
        "font-size:13px; font-weight:bold; }"
        "QPushButton:hover { background:rgba(30,73,118,200); color:white; }");
    connect(bBack, &QPushButton::clicked, this, &MainWindow::on_btnView_Back_clicked);
    lay->addWidget(bBack);

    return page;
}

// ============================================================
//  PAGE 7 — CANCEL TICKET
// ============================================================
QWidget* MainWindow::buildCancelPage() {
    QWidget *page = new QWidget;
    page->setAttribute(Qt::WA_TranslucentBackground);
    QVBoxLayout *lay = new QVBoxLayout(page);
    lay->setContentsMargins(80, 30, 80, 30);
    lay->setSpacing(14);

    QLabel *hdr = new QLabel("[X]  CANCEL TICKET");
    hdr->setAlignment(Qt::AlignCenter);
    hdr->setStyleSheet(
        "font-size:18px; font-weight:900; color:#ff6b6b;"
        "background:rgba(4,14,36,200); border-radius:10px; padding:12px;");
    lay->addWidget(hdr);

    QGroupBox *form = new QGroupBox("  Enter Ticket Details to Cancel");
    QGridLayout *gl = new QGridLayout(form);
    gl->setSpacing(12);
    gl->setColumnStretch(1, 1);

    txtCancelName   = new QLineEdit; txtCancelName->setPlaceholderText("Passenger name");
    txtCancelFlight = new QLineEdit; txtCancelFlight->setPlaceholderText("e.g. PK-301");
    txtCancelSeat   = new QLineEdit; txtCancelSeat->setPlaceholderText("e.g. 12");

    gl->addWidget(makeLabel("Full Name :"), 0, 0); gl->addWidget(txtCancelName,   0, 1);
    gl->addWidget(makeLabel("Flight No :"), 1, 0); gl->addWidget(txtCancelFlight, 1, 1);
    gl->addWidget(makeLabel("Seat No :"),   2, 0); gl->addWidget(txtCancelSeat,   2, 1);
    lay->addWidget(form);
    lay->addStretch();

    QHBoxLayout *br = new QHBoxLayout; br->setSpacing(12);

    QPushButton *bCancel = new QPushButton("Cancel This Ticket");
    bCancel->setFixedHeight(46);
    bCancel->setStyleSheet(
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,"
        "stop:0 #4a0a0a,stop:1 #d32f2f);"
        "color:white; border:none; border-radius:10px;"
        "font-size:14px; font-weight:bold;");

    QPushButton *bBack = new QPushButton("Back to Menu");
    bBack->setFixedHeight(46);
    bBack->setStyleSheet(
        "QPushButton { background:rgba(20,40,70,200); color:#7ab8d4;"
        "border:1.5px solid #1e4976; border-radius:10px;"
        "font-size:13px; font-weight:bold; }"
        "QPushButton:hover { background:rgba(30,73,118,200); color:white; }");

    connect(bCancel, &QPushButton::clicked, this, &MainWindow::on_btnCancelTicket_clicked);
    connect(bBack,   &QPushButton::clicked, this, &MainWindow::on_btnCancel_Back_clicked);
    br->addWidget(bCancel);
    br->addWidget(bBack);
    lay->addLayout(br);

    return page;
}

// ============================================================
//  CONSTRUCTOR
// ============================================================
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("SkyLine Airline Booking System");
    resize(920, 680);
    applyStyle();
    bgImage.load("bg.png");

    QFile f("tickets.txt");
    f.open(QIODevice::WriteOnly | QIODevice::Truncate);
    f.close();

    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(buildLoginPage());      // 0
    stackedWidget->addWidget(buildAdminMenuPage());  // 1
    stackedWidget->addWidget(buildAddFlightPage());  // 2
    stackedWidget->addWidget(buildDataViewPage());   // 3
    stackedWidget->addWidget(buildPassMenuPage());   // 4
    stackedWidget->addWidget(buildBookPage());       // 5
    stackedWidget->addWidget(buildViewPage());       // 6
    stackedWidget->addWidget(buildCancelPage());     // 7

    stackedWidget->setCurrentIndex(PAGE_LOGIN);
    setCentralWidget(stackedWidget);
}

// ============================================================
//  LOGIN SLOTS
// ============================================================
void MainWindow::on_btnAdminLogin_clicked() {
    if (txtUsername->text() == "admin" && txtPassword->text() == "1234") {
        txtUsername->clear();
        txtPassword->clear();
        stackedWidget->setCurrentIndex(PAGE_ADMIN_MENU);
    } else {
        QMessageBox::warning(this, "Login Failed", "Wrong username or password!");
    }
}

void MainWindow::on_btnPassengerLogin_clicked() {
    stackedWidget->setCurrentIndex(PAGE_PASS_MENU);
}

// ============================================================
//  ADMIN MENU SLOTS
// ============================================================
void MainWindow::on_adminMenu_AddFlight_clicked() {
    stackedWidget->setCurrentIndex(PAGE_ADD_FLIGHT);
}

void MainWindow::on_adminMenu_ShowFlights_clicked() {
    QString content;
    if (flights.isEmpty()) {
        content = "No flights registered yet.";
    } else {
        for (auto &f : flights)
            content += f.toDisplay() + "\n\n";
    }
    showDataPage("[=]  ALL FLIGHTS", content.trimmed());
}

void MainWindow::on_adminMenu_TotalFlights_clicked() {
    showDataPage("[#]  TOTAL FLIGHTS",
                 "Total Registered Flights : " + QString::number(Flight::totalFlights));
}

void MainWindow::on_adminMenu_Confidential_clicked() {
    QString content;
    if (flights.isEmpty()) content = "No data available.";
    else for (auto &f : flights) content += f.toConfidential() + "\n";
    showDataPage("[*]  CONFIDENTIAL DATA", content.trimmed());
}

void MainWindow::on_adminMenu_Passengers_clicked() {
    QFile file("tickets.txt");
    QString content;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        content = "No passenger records found.";
    } else {
        QTextStream in(&file);
        int i = 1;
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (line.isEmpty()) continue;
            QStringList p = line.split(" ");
            if (p.size() < 6) continue;
            content += QString("[%1]  Name: %2\n"
                               "     Flight: %3  |  Seat: %4\n"
                               "     Class: %5  |  Rs.%6  |  Pay: %7\n\n")
                           .arg(i++).arg(p[0]).arg(p[1]).arg(p[2])
                           .arg(p[3]).arg(p[4]).arg(p[5]);
        }
        file.close();
        if (content.isEmpty()) content = "No passenger records found.";
    }
    showDataPage("[@]  PASSENGER RECORDS", content.trimmed());
}

void MainWindow::on_adminMenu_Revenue_clicked() {
    showDataPage("[$]  REVENUE REPORT",
                 "Total Revenue Collected :  Rs. " +
                     QString::number(totalRevenue, 'f', 2));
}

void MainWindow::on_adminMenu_SeatAlloc_clicked() {
    QFile file("tickets.txt");
    QString content;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        content = "No records found.";
    } else {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (line.isEmpty()) continue;
            QStringList p = line.split(" ");
            if (p.size() < 3) continue;
            content += QString("Flight: %1  |  Seat: %2  |  Passenger: %3\n")
                           .arg(p[1]).arg(p[2]).arg(p[0]);
        }
        file.close();
        if (content.isEmpty()) content = "No seat allocations found.";
    }
    showDataPage("[S]  SEAT ALLOCATION", content.trimmed());
}

void MainWindow::on_adminMenu_Back_clicked() {
    stackedWidget->setCurrentIndex(PAGE_LOGIN);
}

// ============================================================
//  ADD FLIGHT SLOT
// ============================================================
void MainWindow::on_btnAddFlight_clicked() {
    QString fn  = txtFlightNo->text().trimmed();
    QString air = txtAirline->text().trimmed();
    QString dst = txtDestination->text().trimmed();
    QString dep = txtDeparture->text().trimmed();
    QString arr = txtArrival->text().trimmed();
    int seats   = txtSeats->text().toInt();

    if (fn.isEmpty() || air.isEmpty() || dst.isEmpty() ||
        dep.isEmpty() || arr.isEmpty() || seats <= 0) {
        QMessageBox::warning(this, "Error", "Please fill all fields correctly!");
        return;
    }

    flights.append(Flight(fn, dst, seats, dep, arr, air));

    // ===== PASSENGER DROPDOWN UPDATE =====
    cmbFlights->addItem(
        fn + "  |  " + air + "  ->  " + dst +
        "  |  Dep: " + dep +
        "  |  Seats: " + QString::number(seats)
        );
    // ======================================

    QMessageBox::information(this, "Success",
                             "Flight Added Successfully!\n\n"
                             "Flight No  : " + fn +
                                 "\nAirline    : " + air +
                                 "\nDestination: " + dst +
                                 "\nDeparture  : " + dep +
                                 "\nArrival    : " + arr +
                                 "\nSeats      : " + QString::number(seats));

    txtFlightNo->clear(); txtAirline->clear(); txtDestination->clear();
    txtDeparture->clear(); txtArrival->clear(); txtSeats->clear();
}

void MainWindow::on_btnAddFlight_Back_clicked() {
    stackedWidget->setCurrentIndex(PAGE_ADMIN_MENU);
}

void MainWindow::on_btnDataView_Back_clicked() {
    stackedWidget->setCurrentIndex(PAGE_ADMIN_MENU);
}

// ============================================================
//  PASSENGER MENU SLOTS
// ============================================================
void MainWindow::on_passMenu_Book_clicked() {
    stackedWidget->setCurrentIndex(PAGE_BOOK);
}

void MainWindow::on_passMenu_View_clicked() {
    QFile file("tickets.txt");
    txtViewOutput->clear();
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        txtViewOutput->setPlainText("No tickets found.");
    } else {
        QTextStream in(&file);
        int i = 1;
        QString content;
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (line.isEmpty()) continue;
            QStringList p = line.split(" ");
            if (p.size() < 6) continue;
            content += QString("[%1]  Name: %2\n"
                               "     Flight: %3  |  Seat: %4\n"
                               "     Class: %5  |  Rs.%6  |  Pay: %7\n\n")
                           .arg(i++).arg(p[0]).arg(p[1]).arg(p[2])
                           .arg(p[3]).arg(p[4]).arg(p[5]);
        }
        file.close();
        txtViewOutput->setPlainText(
            content.isEmpty() ? "No tickets found." : content.trimmed());
    }
    stackedWidget->setCurrentIndex(PAGE_VIEW_TICKETS);
}

void MainWindow::on_passMenu_Cancel_clicked() {
    stackedWidget->setCurrentIndex(PAGE_CANCEL);
}

void MainWindow::on_passMenu_Back_clicked() {
    stackedWidget->setCurrentIndex(PAGE_LOGIN);
}

// ============================================================
//  BOOK TICKET SLOT
// ============================================================
void MainWindow::on_btnBookTicket_clicked() {
    QString name = txtPassName->text().trimmed();
    int seat     = txtPassSeat->text().toInt();
    int cls      = cmbClass->currentIndex();
    int pay      = cmbPayment->currentIndex();

    // Flight from dropdown
    int flightIndex = cmbFlights->currentIndex();
    if (flightIndex <= 0) {
        QMessageBox::warning(this, "Error", "Please select a flight from the list!");
        return;
    }

    // index-1 because index 0 = "-- Select a Flight --"
    Flight selectedFlight = flights[flightIndex - 1];
    QString fn = selectedFlight.getFlightNo();

    if (name.isEmpty() || seat <= 0) {
        QMessageBox::warning(this, "Error", "Please fill all fields!");
        return;
    }

    if (seat < 1 || seat > selectedFlight.getSeats()) {
        QMessageBox::warning(this, "Invalid Seat",
                             "Valid seat range for this flight: 1 to " +
                                 QString::number(selectedFlight.getSeats()));
        return;
    }

    // Duplicate seat check
    QFile chk("tickets.txt");
    if (chk.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&chk);
        while (!in.atEnd()) {
            QStringList p = in.readLine().trimmed().split(" ");
            if (p.size() >= 3 && p[1] == fn && p[2].toInt() == seat) {
                QMessageBox::warning(this, "Seat Taken",
                                     "Seat " + QString::number(seat) +
                                         " on flight " + fn + " is already booked!");
                chk.close();
                return;
            }
        }
        chk.close();
    }

    QString seatClass = (cls == 0) ? "Economy"  : "Business";
    int     cost      = (cls == 0) ? 500         : 1000;
    QString payType   = (pay == 0) ? "Cash"      : "Card";

    Payment *p = (pay == 0) ? (Payment*)new Cash() : (Payment*)new Card();
    QString payMsg = p->pay();
    delete p;
    totalRevenue += cost;

    Ticket t(Passenger(name), fn, seat, payType, seatClass, cost);
    txtBookOutput->setPlainText(t.toDisplay() + "\n\n" + payMsg);

    QFile out("tickets.txt");
    out.open(QIODevice::Append | QIODevice::Text);
    QTextStream s(&out);
    s << name << " " << fn << " " << seat << " "
      << seatClass << " " << cost << " " << payType << "\n";
    out.close();

    QMessageBox::information(this, "Booked!", "Ticket Booked Successfully!");
}

void MainWindow::on_btnBook_Back_clicked() {
    stackedWidget->setCurrentIndex(PAGE_PASS_MENU);
}

void MainWindow::on_btnView_Back_clicked() {
    stackedWidget->setCurrentIndex(PAGE_PASS_MENU);
}

// ============================================================
//  CANCEL TICKET SLOT
// ============================================================
void MainWindow::on_btnCancelTicket_clicked() {
    QString name = txtCancelName->text().trimmed();
    QString fn   = txtCancelFlight->text().trimmed();
    int seat     = txtCancelSeat->text().toInt();

    if (name.isEmpty() || fn.isEmpty() || seat <= 0) {
        QMessageBox::warning(this, "Error", "Please fill all fields!");
        return;
    }

    QFile in("tickets.txt");
    QFile temp("temp.txt");
    if (!in.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    temp.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream inS(&in), outS(&temp);
    bool found = false;

    while (!inS.atEnd()) {
        QString line = inS.readLine().trimmed();
        QStringList p = line.split(" ");
        if (p.size() >= 3 &&
            p[0] == name && p[1] == fn && p[2].toInt() == seat) {
            found = true;
            continue;
        }
        if (!line.isEmpty()) outS << line << "\n";
    }
    in.close();
    temp.close();
    QFile::remove("tickets.txt");
    QFile::rename("temp.txt", "tickets.txt");

    if (found) {
        QMessageBox::information(this, "Cancelled",
                                 "Ticket cancelled successfully!\n\n"
                                 "Name   : " + name +
                                     "\nFlight : " + fn +
                                     "\nSeat   : " + QString::number(seat));
        txtCancelName->clear();
        txtCancelFlight->clear();
        txtCancelSeat->clear();
    } else {
        QMessageBox::warning(this, "Not Found",
                             "No matching ticket found!\n"
                             "Check name, flight number and seat.");
    }
}

void MainWindow::on_btnCancel_Back_clicked() {
    stackedWidget->setCurrentIndex(PAGE_PASS_MENU);
}