(deffacts condition
    (PNP Y)
    (RED Y)
    (PIU Y)
)


(defrule rule1
    (PNP Y)
    (RED Y)
    (PIU Y)
    =>
    (printout t "Check the printer-computer cable" crlf)
    (printout t "Ensure printer software is installed" crlf)
    (printout t "Check/replace ink" crlf)
)

(defrule rule2
    (PNP Y)
    (RED Y)
    (PIU N)
    =>
    (printout t "Check/replace ink" crlf)
    (printout t "Check for paper jam" crlf)
)

(defrule rule3
    (PNP Y)
    (RED N)
    (PIU Y)
    =>
    (printout t "Check the power cable" crlf)
    (printout t "Check the printer-computer cable" crlf)
    (printout t "Ensure printer software is installed" crlf)
)

(defrule rule4
    (PNP Y)
    (RED N)
    (PIU Y)
    =>
    (printout t "Check for paper jam" crlf)
)

(defrule rule5
    (PNP Y)
    (RED N)
    (PIU N)
    =>
    (printout t "Ensure printer software is installed" crlf)
    (printout t "Check/replace ink" crlf)
)

(defrule rule6
    (PNP N)
    (RED Y)
    (PIU Y)
    =>
    (printout t "Check/replace ink" crlf)
)

(defrule rule7
    (PNP N)
    (RED N)
    (PIU Y)
    =>
    (printout t "Ensure printer software is installed" crlf)
)
