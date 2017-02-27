(deffacts condition
    (PNP Y)
    (RED N)
    (PIU N)
)


(defrule power-cable
    (PNP Y)
    (RED N)
    (PIU Y)
    =>
    (printout t "Check the power cable" crlf)
)

(defrule computer-cable
    (PNP Y)
    (PIU Y)
    =>
    (printout t "Check the printer-computer cable" crlf)
)

(defrule software
    (PIU Y)
    =>
    (printout t "Ensure printer software is installed" crlf)
)

(defrule ink
    (RED Y)
    =>
    (printout t "Check/replace ink" crlf)
)

(defrule paper
    (PNP Y)
    (PIU N)
    =>
    (printout t "Check for paper jam" crlf)
)
