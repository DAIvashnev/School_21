COMMENT ON TABLE person_discounts IS 'Table discounts';
COMMENT ON COLUMN person_discounts.id IS 'Primary key';
COMMENT ON COLUMN person_discounts.person_id IS 'Identification of a person';
COMMENT ON COLUMN person_discounts.pizzeria_id IS 'Identification of a pizzeria';
COMMENT ON COLUMN person_discounts.discount IS 'Discount in percent for person';