(deftemplate fz-height
0 220
( (small (140 1) (160 0))
  (medium (150 0) (165 1) (175 0))
  (high (170 0) (185 1))
))

(deftemplate fz-weight
0 160
( (small (40 1) (70 0))  
  (high (80 0) (110 1))
  (medium not [ small or high ])
))

(deftemplate person
(slot name)
(slot height (type FUZZY-VALUE fz-height))
(slot weight (type FUZZY-VALUE fz-weight))
)

(defrule big-person (declare (CF 0.8))
(person (name ?n) (weight high) (height high))
=>
(printout t ?n " is a big person" crlf)
(assert (big ?n))
)

(deffacts persoane
(person (name Ion) (height (179 0) (180 1) (181 0)) (weight (99 0) (100 1) (101 0)))
(person (name Vasile) (height (179 0) (180 1) (181 0)) (weight (149 0) (150 1) (151 0)))
(fit Ion) CF 0.5
)

(defrule athlete
(big ?n)
(fit ?n)
=>
(assert (athlete ?n))
)

(defrule defuzzy
(athlete ?n)
(person (name ?n) (weight ?w))
=>
(printout t "athlete weight is " (moment-defuzzify ?w) crlf)
)

(defrule notfit
(person (name ?n) (weight very high))
=>
(assert (notfit ?n))
)
