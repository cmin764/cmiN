#cs
# Send mass messages through Yahoo! Messenger to IDs from a text file.
# 08.05.2012 cmiN
#ce


; constants
Const $MESS = "Yahoo! Messenger" ; messenger window title (default for v11.5)
Const $DLAY = 200 ; delay in miliseconds, for spam protection ... who knows


Func send_message($id, $message)
    Send($id)
    Send("{Enter}")
    WinWaitActive($id) ; comment this if you're not sure that the target id
    ;Sleep($DLAY) ; have the same alias and of course uncomment this to let the window appear
    Send($message)
    Send("{Enter}")
    Sleep($DLAY)
    Send("{Esc}")
EndFunc


Func main()
    ; path to message file
    ;$path = "msg.txt"
    $path = InputBox("Input", "Enter path to message file.")
    If $path == "" Then Exit
    $file = FileOpen($path, 0)
    If $file == -1 Then Exit
    $message = FileRead($file)
    FileClose($file)
    ; path to IDs file
    ;$path = "ids.txt"
    $path = InputBox("Input", "Enter path to IDs file.")
    If $path == "" Then Exit
    $file = FileOpen($path, 0)
    If $file == -1 Then Exit
    ; process
    MsgBox(0, "Info", "Sending '" & $message & "' to all IDs." & @LF & "Launch the client and press OK to start!")
    $handle = WinActivate("Yahoo! Messenger") ; make messenger window active
    If Not $handle Then
        MsgBox(16, "Error", $MESS & " window not found.")
        Exit
    EndIf
    While 1
        $line = FileReadLine($file)
        If @error == -1 Then ExitLoop
        send_message($line, $message)
    WEnd
    FileClose($file)
    MsgBox(0, "Info", "Finished.")
EndFunc


main()