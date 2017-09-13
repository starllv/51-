VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   1140
   ClientLeft      =   11070
   ClientTop       =   7155
   ClientWidth     =   2460
   LinkTopic       =   "Form1"
   ScaleHeight     =   1140
   ScaleWidth      =   2460
   Begin VB.TextBox Text1 
      Height          =   270
      Left            =   840
      TabIndex        =   0
      Top             =   360
      Width           =   735
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   960
      Top             =   960
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
MSComm1.Settings = "9600,N,8,1"
MSComm1.CommPort = 4  '根据自己的情况设定串口
MSComm1.InBufferSize = 8
MSComm1.OutBufferSize = 2
If MSComm1.PortOpen = True Then MSComm1.PortOpen = False
MSComm1.RThreshold = 4
MSComm1.SThreshold = 1
MSComm1.InputLen = 0
MSComm1.InputMode = comInputModeText
If MSComm1.PortOpen = False Then MSComm1.PortOpen = True
MSComm1.InBufferCount = 0
Me.Caption = "温度"
Text1.Text = "00.0"
End Sub

Private Sub MSComm1_OnComm()
Dim rec As String
Select Case MSComm1.CommEvent
Case comEvReceive
rec = MSComm1.Input
Text1.Text = rec
MSComm1.InBufferCount = 0
End Select
End Sub

