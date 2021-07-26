The timing of data capture is important. The best time is when the form is being submitted. A form can be submitted in many ways:

Any of the above objects will trigger the event DISPID_HTMLFORMELEMENTEVENTS2_ONSUBMIT.

In this case, we've to handle:

When an object of type <INPUT TYPE=submit> or <INPUT TYPE=image> or <BUTTON TYPE=submit> is clicked by the left mouse key, or the Enter key or space bar key is pressed.
By calling form.submit in an event handler of an object's mouse or key event handler.
DISPID_HTMLELEMENTEVENTS2_ONKEYPRESS and
DISPID_HTMLELEMENTEVENTS2_ONCLICK
Once you know when to capture the data, the rest is very easy. All you do is walk through the element collection and retrieve the user ID and password.
_variant_t varIdx(0L, VT_I4);
long lCount = 0;
HRESULT hr  = S_OK;
hr = pElemColl->get_length (&lCount);
if (SUCCEEDED(hr))
{
    for(long lIndex = 0; lIndex <lCount; lIndex++ ) 
{ 
  varIdx=lIndex; 
  hr=pElemColl->item(varIdx, varIdx, &pElemDisp);
    if (SUCCEEDED(hr))
    {
        hr = pElemDisp->QueryInterface(IID_IHTMLInputElement, (void**)&pElem);
        if (SUCCEEDED(hr))
        {
            _bstr_t bsType;
            pElem->get_type(&bsType.GetBSTR());
            if(bsType.operator ==(L"text"))
            {
                pElem->get_value(&bsUserId.GetBSTR());
            }
            else if(bsType.operator==(L"password"))
            {
                pElem->get_value(&bsPassword.GetBSTR());
            }
            pElem->Release();
        }

        pElemDisp->Release();
    }
    if(bsUserId.GetBSTR() && bsPassword.GetBSTR() && 
      ( bsUserId.operator!=(L"") && bsPassword.operator!=(L"") ) )
    {
        return;
    }            

    }
}
