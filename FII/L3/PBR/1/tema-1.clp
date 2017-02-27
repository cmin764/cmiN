(deffacts condition
    (PNP Y)
    (RED N)
    (PIU Y)
)


(defrule power-cable
    (PNP Y)
    (RED N)
    (PIU Y)
    =>
    (printout t "Check the power cable" crlf)
)

(defrule computer-cable
    (or
        (and
            (PNP Y)
            (RED Y)
            (PIU Y)
        )
        (and
            (PNP Y)
            (RED N)
            (PIU Y)
        )
    )
    =>
    (printout t "Check the printer-computer cable" crlf)
)

(defrule software
    (or
        (and
            (PNP Y)
            (RED Y)
            (PIU Y)
        )
        (and
            (PNP Y)
            (RED N)
            (PIU Y)
        )
        (and
            (PNP N)
            (RED Y)
            (PIU Y)
        )
        (and
            (PNP N)
            (RED N)
            (PIU Y)
        )
    )
    =>
    (printout t "Ensure printer software is installed" crlf)
)

(defrule ink
    (or
        (and
            (PNP Y)
            (RED Y)
            (PIU Y)
        )
        (and
            (PNP Y)
            (RED Y)
            (PIU N)
        )
        (and
            (PNP N)
            (RED Y)
            (PIU Y)
        )
        (and
            (PNP N)
            (RED Y)
            (PIU N)
        )
    )
    =>
    (printout t "Check/replace ink" crlf)
)

(defrule paper
    (or
        (and
            (PNP Y)
            (RED Y)
            (PIU Y)
        )
        (and
            (PNP Y)
            (RED N)
            (PIU Y)
        )
    )
    =>
    (printout t "Check for paper jam" crlf)
)
